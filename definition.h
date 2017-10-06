struct song
{
	char *songName;
	struct song *next;
	struct song *prev;
};

struct feature
{
	struct song *ptr;
};

