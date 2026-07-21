#include <libintl.h>
#include <locale.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <dirent.h>
#include <fcntl.h>
#include <stdio.h>
#include <errno.h>
#include <grp.h>
#include <pwd.h>

enum mode
{
	NO_RECURSE_NO_SYMLINKS,   // for each file, chown
	NO_RECURSE_SYMLINKS,      // for each file, follow, chown
	RECURSE_NO_SYMLINKS,      // for each tree, chown
	RECURSE_COMMAND_SYMLINKS, // for each followed tree, chown
	RECURSE_ALL_SYMLINKS      // for each followed tree, follow, chown
};

uid_t uid = -1;
gid_t gid = -1;
enum mode mode = NO_RECURSE_SYMLINKS;
int force = 0;

static int
_recurse (const char *self, const char *path, int recursion)
{
	if (recursion > 2096)
	{
		fprintf(stderr, gettext("%s: Recursion limit -- 2096 -- reached\n"),
			self);
		return 1;
	}

	int likesyms = 1;
	if (mode == RECURSE_NO_SYMLINKS ||
		(
			mode == RECURSE_COMMAND_SYMLINKS &&
			recursion > 0
		))
	{
		likesyms = 0;
	}

	// treat as file
	if (likesyms)
	{
		if (chown(path, uid, gid) && !force)
		{
			fprintf(stderr, gettext(
				"%s: Failed to change ownership for file `%s', %s\n"),
				self, path, strerror(errno));
			return 1;
		}
	}
	else
	{

		if (lchown(path, uid, gid) && !force)
		{
			fprintf(stderr, gettext(
				"%s: Failed to change ownership for file `%s', %s\n"),
				self, path, strerror(errno));
			return 1;
		}
	}

	// open as directory
	int oflags = O_DIRECTORY|O_RDONLY;
	if (!likesyms)
	{
		oflags |= O_NOFOLLOW;
	}
	int fd = open(path, oflags);

	// the directory got opened
	if (fd != -1)
	{
		// recurse
		DIR *dirp = fdopendir(fd);
		if (!dirp)
		{
			close(fd);

			if (force) return 0;

			fprintf(stderr, gettext("%s: Failed to open directory `%s', %s\n"),
				self, path, strerror(errno));
			return 1;
		}

		struct dirent *dirent;

		// the name vector
		size_t namecp = strlen(path)+2;
		char  *name   = malloc(namecp);
		if (!name)
		{
			fprintf(stderr, gettext("%s: %s\n"), self, strerror(errno));
			return 1;
		}
		strcpy(name, path);
		strcat(name, "/");
		const size_t namesz = namecp; // the size of path + '/' + 0

		while (1)
		{
			dirent = readdir(dirp);
			if (!dirent) break;

			const char *d_name = dirent->d_name;

			// skip these or else we'll go forever
			if (!strcmp(d_name, ".")) continue;
			if (!strcmp(d_name, "..")) continue;

			size_t newsize = namesz+strlen(d_name);
			if (newsize > namecp)
			{
				namecp = newsize;
				void *buf = realloc(name, namecp);
				if (!buf)
				{
					if (force) // try to continue
					{
						namecp = 0;
						continue;
					}

					fprintf(stderr, gettext("%s: %s\n"), self, strerror(errno));
					free(name);
					return 1;
				}

				name = buf;
			}
			// copy over the name
			strcpy(&name[namesz-1], d_name);

			if (_recurse(self, name, recursion+1) && !force)
			{
				closedir(dirp);
				free(name);
				return 1;
			}
		}
		free(name);
		closedir(dirp);
	}
	return 0; // its not a directory
}

int
main (int argc, char *argv[])
{
	setlocale(LC_ALL, "");
	textdomain("chown");

	// arguments
	int c;
	do
	{
		c = getopt(argc, argv, "fhHPLR");

		switch (c)
		{
		case 'f':
			force = 1;
			break;
		case 'h':
			mode = NO_RECURSE_NO_SYMLINKS;
			break;
		case 'R':
		case 'P':
			mode = RECURSE_NO_SYMLINKS;
			break;
		case 'L':
			mode = RECURSE_ALL_SYMLINKS;
			break;
		case 'H':
			mode = RECURSE_COMMAND_SYMLINKS;
			break;
		case -1:
			break;
		case '?':
		case ':':
			return 1;
		}
	} while (c != -1);

	// get user and group
	if (optind == argc)
	{
		fprintf(stderr, gettext("%s: No user name was provided\n"), argv[0]);
		return 1;
	}
	char *user  = argv[optind];
	optind++;
	char *group = NULL;
	for (long i = 0; user[i]; i++)
	{
		if (user[i] == ':')
		{
			group   = &user[i+1];
			user[i] = '\0';
			break;
		}
	}

	// get user ID and group ID
	// get uid
	// errno = -1;
	struct passwd *passwd = getpwnam(user);
	if (!passwd)
	{
		// GLibC is crap, it sets errno to ESUCCESS instead of not modifying it
		// like POSIX says. Therefore this isn't useful until mimik libc comes
		// out

		// if (errno >= 0)
		// {
		// 	fprintf(stderr, gettext("%s: Failed to get user `%s', %s\n"),
		// 		argv[0], user, strerror(errno));
		// 	return 1;
		// }

		// check for numeric user value
		char *endp;
		uid = strtol(user, &endp, 0);
		if (endp == user) // if not all the user was consumed
		{
			fprintf(stderr, gettext("%s: Failed to find user or uid `%s'\n"),
				argv[0], user);
			return 1;
		}
	}
	else
	{
		uid = passwd->pw_uid;
	}

	// get gid
	if (group)
	{
		// errno = -1;
		struct group *grp = getgrnam(group);
		if (!grp)
		{
			// GLibC is crap, it sets errno to ESUCCESS instead of not modifying
			// it like POSIX says. Therefore this isn't useful until mimik libc
			// comes out

			// if (errno >= 0)
			// {
			// 	fprintf(stderr, gettext("%s: Failed to get group `%s', %s\n"),
			// 		argv[0], group, strerror(errno));
			// 	return 1;
			// }

			// check for numeric group value
			char *endp;
			gid = strtol(group, &endp, 0);
			if (endp == group) // if not all the group was consumed
			{
				fprintf(stderr,
					gettext("%s: Failed to find group or gid `%s'\n"),
					argv[0], group);
				return 1;
			}
		}
		else
		{
			gid = grp->gr_gid;
		}
	}

	// change files
	switch (mode)
	{
	case NO_RECURSE_NO_SYMLINKS:
		for (int i = optind; i<argc; i++)
		{
			if (lchown(argv[i], uid, gid) && !force)
			{
				fprintf(stderr, gettext(
					"%s: Failed to change ownership of file `%s', %s\n"),
					argv[0], argv[i], strerror(errno));
				return 1;
			}
		}
		break;
	case NO_RECURSE_SYMLINKS:
		for (int i = optind; i<argc; i++)
		{
			if (chown(argv[i], uid, gid) && !force)
			{
				fprintf(stderr, gettext(
					"%s: Failed to change ownership of file `%s', %s\n"),
					argv[0], argv[i], strerror(errno));
				return 1;
			}
		}
		break;
	case RECURSE_NO_SYMLINKS:
	case RECURSE_COMMAND_SYMLINKS:
	case RECURSE_ALL_SYMLINKS:
		for (int i = optind; i<argc; i++)
		{
			if (_recurse(argv[0], argv[i], 0))
			{
				return 1;
			}
		}
		break;
	}

	return 0;
}
