# Name

cat, `.cat` - Message catalogue file, part of libc


# Synopsis

```C
#include <nl_types.h>

size_t nl_ent_index (int set, int message); // index into table

struct nl_catalogue
{
	char          magic[4]; // "MCAT"
	unsigned char rev; // 0

	size_t entries;
	struct
	{
		int    set;
		int    message;
		off_t  index; // into data
	} table[.entries];
	char data [];
};
```


# Description

The position of each *set*-*message* pair in *data* shall be that of the corresponding entry in *table* at *index*. Each *set*-*message* pair in *table* shall be position at index `nl_ent_index(set, message)` mod *entries*. If the index is already occupied by another entry then the next entry in *table* shall be used, this increment shall be mod *entries* and be repeated until an open entry is found. In searching the indexed value shall be check if *set* and *message* match the query.


# Extended Description

This data structure is akin to a hash table.


# Future Directions

There are no future directions.


# See Also

[catopen](catopen.3) - Open existing catalogue

[catgets](catgets.3) - Get message from catalogue

[gencat](gencat.1) - Generate new catalogue from message file

[catgets](catgets.1) - Get message from catalogue, interface for scripting

[hashtable](https://en.wikipedia.org/wiki/Hash_table#Open_addressing) - Wikipedia entry on hash-tables, used in this implementation
