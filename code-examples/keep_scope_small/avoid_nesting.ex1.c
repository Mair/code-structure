
esp_err_t teach_c_to_person(person_t *person)
{
    if (person.age > 8)
    {
        if (person.age < 90)
        {
            if (person.wants_to_learn_c == true)
            {
                while (person.understands_pointers == false)
                {
                    explain_pointers(person);
                }
            }
        }
    }
}