// Replace the variable names so that the below is meaning-full

static volatile float cc;

float get_air_temperature_fahrenheit(void)
{
    float c;
    read_sensor_air_temperature(&c);
    cc = c;
    float f = convert_centigrade_to_fahrenheit(c);
    return f;
}

void read_sensor_air_temperature(float *c)
{
    *c = read_sensor();
}