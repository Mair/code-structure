
#define MAX_DOGS 2
#define MAX_CATS 2

typedef struct dog_t
{
    char name[30];
} dog_t;

typedef struct cat_t
{
    char name[30];
} cat_t;

typedef struct family_t
{
    cat_t cats[MAX_CATS];
    dog_t dogs[MAX_DOGS];
} family_t;

typedef struct aStruct_t
{
    family_t family;
} aStruct_t;
