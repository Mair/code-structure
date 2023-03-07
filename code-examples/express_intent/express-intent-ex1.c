// based on the comments, please make the code readable

// sends alerts
void do_it()
{
    // get water temperature
    float wt = get_wt();

    // if water temperature outside of range send alert
    if (!(wt > wmit && wt < wmat))
        a();

    // get water level
    float wl = get_wtl();

    // if water level outside of range send alert
    if (!(wl > wlit && wl < wlat))
        a();
}