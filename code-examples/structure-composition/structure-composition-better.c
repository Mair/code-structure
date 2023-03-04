

typedef struct dog_t
{
    char dog1_name[30];
    char dog2_name[30];
} dog_t;

typedef struct cat_t
{
    char cat1_name[30];
    char cat2_name[30];
} cat_t;

typedef struct family_t
{
    cat_t cats;
    dog_t dogs;
} family_t;

typedef struct aStruct_t
{
    family_t family;
} aStruct_t;
