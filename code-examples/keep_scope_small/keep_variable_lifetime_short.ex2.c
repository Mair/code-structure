
const float MIN = 5;

float range;

const float MAX = 20;

float normalized;

float normalize_percent(float value)
{
    float val_minus_min;
    float percent;
    if (!(value > MIN && value < MAX))
        return -1;

    val_minus_min = value - MIN;
    range = MAX - MIN;
    normalized = val_minus_min / range;
    percent = normalized *= 100;
    return percent;
}