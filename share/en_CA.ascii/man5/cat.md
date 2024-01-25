# Prologue

This manual is part of the Mimik System Tree, other implementations may differ. Some compatibility with existing standards may be met but to do not expect any.


# Name

cat, `.cat` - Message catalogue file, part of libc


# Synopsis

```C
#include <nl_types.h>

size_t nl_ent_index (int set, int message);

struct nl_catalogue
{
    size_t entries;
    struct nl_entry
    {
        int  set;
        int  message;
        char data[NL_TEXTMAX];
    } entry[.entries];
};
```


# Description

Each entry shall be positioned at index `nl_ent_index(set, message)` mod *entries* inside array *entry*. If the index is already occupied then the next index shall try to be used until an open index is found; this increment shall be mod *entries*. Searching shall use the same indexing but each check shall test is the *set* and *message* match the query before returning *data*.


# Extended Description

This data structure is akin to a hash table.


# Future Directions

There are no future directions.


# See Also

[catopen](catopen.3) - Open existing catalogue

[catgets](catgets.3) - Get message from catalogue

[gencat](gencat.1) - Generate new catalogue from message file

[catgets](catgets.1) - Get message from catalogue, interface for scripting
