
float value;

...;

void get_temperature()
{
    char *id = "some bus id";
    float val = get_value(id);

    some_call_2();

    some_call_3();

    some_call_4();

    value = some_call_5(val);
}