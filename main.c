#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h> 
#include <sys/stat.h>

struct entry
{
    char county[100]; // County name
    char state[50];   // State name

    // Age demographics
    float age_65_plus;  // Percent 65 and older
    float age_under_18; // Percent under 18
    float age_under_5;  // Percent under 5

    // Education
    float edu_bachelor_plus; // Bachelor's degree or higher
    float edu_high_school;   // High school or higher

    // Employment
    uint32_t nonemploy_est; // Nonemployer establishments
    uint32_t private_emp;   // Private non-farm employment
    float private_emp_chg;  // Private non-farm employment percent change
    uint32_t private_est;   // Private non-farm establishments

    // Ethnicities
    float eth_ai_an;          // American Indian and Alaska Native alone
    float eth_asian;          // Asian alone
    float eth_black;          // Black alone
    float eth_hispanic;       // Hispanic or Latino
    float eth_nh_pi;          // Native Hawaiian and Other Pacific Islander alone
    float eth_multi;          // Two or more races
    float eth_white;          // White alone
    float eth_white_non_hisp; // White alone, not Hispanic or Latino

    // Housing
    float homeown_rate;       // Homeownership rate
    uint32_t households;      // Number of households
    uint32_t housing_units;   // Housing units
    uint32_t median_home_val; // Median value of owner-occupied units
    float persons_per_hh;     // Persons per household
    float multi_unit_struct;  // Units in multi-unit structures

    // Income
    uint32_t median_income;  // Median household income
    uint32_t per_cap_income; // Per capita income
    float poverty_rate;      // Persons below poverty level

    // Miscellaneous
    uint32_t building_permits; // Building permits
    float foreign_born;        // Percent foreign born
    float land_area;           // Land area (square miles)
    float lang_non_english;    // Language other than English at home
    float same_house_1yr;      // Living in the same house +1 years
    uint64_t manuf_shipments;  // Manufacturers shipments
    float mean_travel_time;    // Mean travel time to work (minutes)
    float percent_female;      // Percent female
    uint32_t veterans;         // Veterans

    // Population
    uint32_t pop_2010; // Population (2010)
    uint32_t pop_2014; // Population (2014)
    float pop_chg;     // Population percent change
    float pop_density; // Population per square mile

    // Sales
    uint64_t sales_food_accom; // Accommodation and food services sales
    uint64_t sales_wholesale;  // Merchant wholesaler sales
    uint64_t sales_retail;     // Retail sales
    uint32_t sales_per_capita; // Retail sales per capita

    // Firms ownership
    uint32_t firms_ai_owned;    // American Indian-owned firms
    uint32_t firms_asian_owned; // Asian-owned firms
    uint32_t firms_black_owned; // Black-owned firms
    uint32_t firms_hisp_owned;  // Hispanic-owned firms
    uint32_t firms_nh_pi_owned; // Native Hawaiian and Other Pacific Islander-owned firms
    uint32_t firms_total;       // Total firms
    uint32_t firms_women_owned; // Women-owned firms
};

void remove_quotes(char *str)
{
    char *src = str, *dest = str;
    while (*src)
    {
        if (*src != '\"')
        {
            *dest++ = *src;
        }
        src++;
    }
    *dest = '\0';
}

int load_data(const char *filename, struct entry **entries, int *count)
{
    FILE *file = fopen(filename, "r");
    if (!file)
    {
        fprintf(stderr, "Error: Unable to open file '%s'\n", filename);
        return 0;
    }

    char line[4096];
    if (!fgets(line, sizeof(line), file))
    {
        fprintf(stderr, "Error: File '%s' is empty or invalid.\n", filename);
        fclose(file);
        return 0;
    }

    printf("Header line: %s\n", line);

    *entries = NULL;
    *count = 0;
    int line_number = 2; 

    while (fgets(line, sizeof(line), file))
    {
        // printf("Reading line %d: %s\n", line_number, line);

        struct entry e;
        char *token = strtok(line, ",");
        if (!token)
        {
            fprintf(stderr, "Error: Malformed line %d (missing county)\n", line_number);
            line_number++;
            continue;
        }
        remove_quotes(token);
        strncpy(e.county, token, sizeof(e.county) - 1);
        e.county[sizeof(e.county) - 1] = '\0'; // Ensure null termination

        token = strtok(NULL, ",");
        if (!token)
        {
            fprintf(stderr, "Error: Malformed line %d (missing state)\n", line_number);
            line_number++;
            continue;
        }
        remove_quotes(token);
        strncpy(e.state, token, sizeof(e.state) - 1);
        e.state[sizeof(e.state) - 1] = '\0'; // Ensure null termination

        // Age demographics
        token = strtok(NULL, ",");
        if (!token)
        {
            fprintf(stderr, "Error: Malformed line %d (missing age_65_plus)\n", line_number);
            line_number++;
            continue;
        }
        remove_quotes(token);
        e.age_65_plus = atof(token);

        token = strtok(NULL, ",");
        if (!token)
        {
            fprintf(stderr, "Error: Malformed line %d (missing age_under_18)\n", line_number);
            line_number++;
            continue;
        }
        remove_quotes(token);
        e.age_under_18 = atof(token);

        token = strtok(NULL, ",");
        if (!token)
        {
            fprintf(stderr, "Error: Malformed line %d (missing age_under_5)\n", line_number);
            line_number++;
            continue;
        }
        remove_quotes(token);
        e.age_under_5 = atof(token);

        // Education
        token = strtok(NULL, ",");
        if (!token)
        {
            fprintf(stderr, "Error: Malformed line %d (missing edu_bachelor_plus)\n", line_number);
            line_number++;
            continue;
        }
        remove_quotes(token);
        e.edu_bachelor_plus = atof(token);

        token = strtok(NULL, ",");
        if (!token)
        {
            fprintf(stderr, "Error: Malformed line %d (missing edu_high_school)\n", line_number);
            line_number++;
            continue;
        }
        remove_quotes(token);
        e.edu_high_school = atof(token);

        // Employment
        token = strtok(NULL, ",");
        if (!token)
        {
            fprintf(stderr, "Error: Malformed line %d (missing nonemploy_est)\n", line_number);
            line_number++;
            continue;
        }
        remove_quotes(token);
        e.nonemploy_est = atoi(token);

        token = strtok(NULL, ",");
        if (!token)
        {
            fprintf(stderr, "Error: Malformed line %d (missing private_emp)\n", line_number);
            line_number++;
            continue;
        }
        remove_quotes(token);
        e.private_emp = atoi(token);

        token = strtok(NULL, ",");
        if (!token)
        {
            fprintf(stderr, "Error: Malformed line %d (missing private_emp_chg)\n", line_number);
            line_number++;
            continue;
        }
        remove_quotes(token);
        e.private_emp_chg = atof(token);

        token = strtok(NULL, ",");
        if (!token)
        {
            fprintf(stderr, "Error: Malformed line %d (missing private_est)\n", line_number);
            line_number++;
            continue;
        }
        remove_quotes(token);
        e.private_est = atoi(token);

        // Ethnicities
        token = strtok(NULL, ",");
        if (!token)
        {
            fprintf(stderr, "Error: Malformed line %d (missing eth_ai_an)\n", line_number);
            line_number++;
            continue;
        }
        remove_quotes(token);
        e.eth_ai_an = atof(token);

        token = strtok(NULL, ",");
        if (!token)
        {
            fprintf(stderr, "Error: Malformed line %d (missing eth_asian)\n", line_number);
            line_number++;
            continue;
        }
        remove_quotes(token);
        e.eth_asian = atof(token);

        token = strtok(NULL, ",");
        if (!token)
        {
            fprintf(stderr, "Error: Malformed line %d (missing eth_black)\n", line_number);
            line_number++;
            continue;
        }
        remove_quotes(token);
        e.eth_black = atof(token);

        token = strtok(NULL, ",");
        if (!token)
        {
            fprintf(stderr, "Error: Malformed line %d (missing eth_hispanic)\n", line_number);
            line_number++;
            continue;
        }
        remove_quotes(token);
        e.eth_hispanic = atof(token);

        token = strtok(NULL, ",");
        if (!token)
        {
            fprintf(stderr, "Error: Malformed line %d (missing eth_nh_pi)\n", line_number);
            line_number++;
            continue;
        }
        remove_quotes(token);
        e.eth_nh_pi = atof(token);

        token = strtok(NULL, ",");
        if (!token)
        {
            fprintf(stderr, "Error: Malformed line %d (missing eth_multi)\n", line_number);
            line_number++;
            continue;
        }
        remove_quotes(token);
        e.eth_multi = atof(token);

        token = strtok(NULL, ",");
        if (!token)
        {
            fprintf(stderr, "Error: Malformed line %d (missing eth_white)\n", line_number);
            line_number++;
            continue;
        }
        remove_quotes(token);
        e.eth_white = atof(token);

        token = strtok(NULL, ",");
        if (!token)
        {
            fprintf(stderr, "Error: Malformed line %d (missing eth_white_non_hisp)\n", line_number);
            line_number++;
            continue;
        }
        remove_quotes(token);
        e.eth_white_non_hisp = atof(token);

        // Housing
        token = strtok(NULL, ",");
        if (!token)
        {
            fprintf(stderr, "Error: Malformed line %d (missing homeown_rate)\n", line_number);
            line_number++;
            continue;
        }
        remove_quotes(token);
        e.homeown_rate = atof(token);

        token = strtok(NULL, ",");
        if (!token)
        {
            fprintf(stderr, "Error: Malformed line %d (missing households)\n", line_number);
            line_number++;
            continue;
        }
        remove_quotes(token);
        e.households = atoi(token);

        token = strtok(NULL, ",");
        if (!token)
        {
            fprintf(stderr, "Error: Malformed line %d (missing housing_units)\n", line_number);
            line_number++;
            continue;
        }
        remove_quotes(token);
        e.housing_units = atoi(token);

        token = strtok(NULL, ",");
        if (!token)
        {
            fprintf(stderr, "Error: Malformed line %d (missing median_home_val)\n", line_number);
            line_number++;
            continue;
        }
        remove_quotes(token);
        e.median_home_val = atoi(token);

        token = strtok(NULL, ",");
        if (!token)
        {
            fprintf(stderr, "Error: Malformed line %d (missing persons_per_hh)\n", line_number);
            line_number++;
            continue;
        }
        remove_quotes(token);
        e.persons_per_hh = atof(token);

        token = strtok(NULL, ",");
        if (!token)
        {
            fprintf(stderr, "Error: Malformed line %d (missing multi_unit_struct)\n", line_number);
            line_number++;
            continue;
        }
        remove_quotes(token);
        e.multi_unit_struct = atof(token);

        // Income
        token = strtok(NULL, ",");
        if (!token)
        {
            fprintf(stderr, "Error: Malformed line %d (missing median_income)\n", line_number);
            line_number++;
            continue;
        }
        remove_quotes(token);
        e.median_income = atoi(token);

        token = strtok(NULL, ",");
        if (!token)
        {
            fprintf(stderr, "Error: Malformed line %d (missing per_cap_income)\n", line_number);
            line_number++;
            continue;
        }
        remove_quotes(token);
        e.per_cap_income = atoi(token);

        token = strtok(NULL, ",");
        if (!token)
        {
            fprintf(stderr, "Error: Malformed line %d (missing poverty_rate)\n", line_number);
            line_number++;
            continue;
        }
        remove_quotes(token);
        e.poverty_rate = atof(token);

        // Miscellaneous
        token = strtok(NULL, ",");
        if (!token)
        {
            fprintf(stderr, "Error: Malformed line %d (missing building_permits)\n", line_number);
            line_number++;
            continue;
        }
        remove_quotes(token);
        e.building_permits = atoi(token);

        token = strtok(NULL, ",");
        if (!token)
        {
            fprintf(stderr, "Error: Malformed line %d (missing foreign_born)\n", line_number);
            line_number++;
            continue;
        }
        remove_quotes(token);
        e.foreign_born = atof(token);

        token = strtok(NULL, ",");
        if (!token)
        {
            fprintf(stderr, "Error: Malformed line %d (missing land_area)\n", line_number);
            line_number++;
            continue;
        }
        remove_quotes(token);
        e.land_area = atof(token);

        token = strtok(NULL, ",");
        if (!token)
        {
            fprintf(stderr, "Error: Malformed line %d (missing lang_non_english)\n", line_number);
            line_number++;
            continue;
        }
        remove_quotes(token);
        e.lang_non_english = atof(token);

        token = strtok(NULL, ",");
        if (!token)
        {
            fprintf(stderr, "Error: Malformed line %d (missing same_house_1yr)\n", line_number);
            line_number++;
            continue;
        }
        remove_quotes(token);
        e.same_house_1yr = atof(token);

        token = strtok(NULL, ",");
        if (!token)
        {
            fprintf(stderr, "Error: Malformed line %d (missing manuf_shipments)\n", line_number);
            line_number++;
            continue;
        }
        remove_quotes(token);
        e.manuf_shipments = atoll(token);

        token = strtok(NULL, ",");
        if (!token)
        {
            fprintf(stderr, "Error: Malformed line %d (missing mean_travel_time)\n", line_number);
            line_number++;
            continue;
        }
        remove_quotes(token);
        e.mean_travel_time = atof(token);

        token = strtok(NULL, ",");
        if (!token)
        {
            fprintf(stderr, "Error: Malformed line %d (missing percent_female)\n", line_number);
            line_number++;
            continue;
        }
        remove_quotes(token);
        e.percent_female = atof(token);

        token = strtok(NULL, ",");
        if (!token)
        {
            fprintf(stderr, "Error: Malformed line %d (missing veterans)\n", line_number);
            line_number++;
            continue;
        }
        remove_quotes(token);
        e.veterans = atoi(token);

        // Population
        token = strtok(NULL, ",");
        if (!token)
        {
            fprintf(stderr, "Error: Malformed line %d (missing pop_2010)\n", line_number);
            line_number++;
            continue;
        }
        remove_quotes(token);
        e.pop_2010 = atoi(token);

        token = strtok(NULL, ",");
        if (!token)
        {
            fprintf(stderr, "Error: Malformed line %d (missing pop_2014)\n", line_number);
            line_number++;
            continue;
        }
        remove_quotes(token);
        e.pop_2014 = atoi(token);

        token = strtok(NULL, ",");
        if (!token)
        {
            fprintf(stderr, "Error: Malformed line %d (missing pop_chg)\n", line_number);
            line_number++;
            continue;
        }
        remove_quotes(token);
        e.pop_chg = atof(token);

        token = strtok(NULL, ",");
        if (!token)
        {
            fprintf(stderr, "Error: Malformed line %d (missing pop_density)\n", line_number);
            line_number++;
            continue;
        }
        remove_quotes(token);
        e.pop_density = atof(token);

        // Sales
        token = strtok(NULL, ",");
        if (!token)
        {
            fprintf(stderr, "Error: Malformed line %d (missing sales_food_accom)\n", line_number);
            line_number++;
            continue;
        }
        remove_quotes(token);
        e.sales_food_accom = atoll(token);

        token = strtok(NULL, ",");
        if (!token)
        {
            fprintf(stderr, "Error: Malformed line %d (missing sales_wholesale)\n", line_number);
            line_number++;
            continue;
        }
        remove_quotes(token);
        e.sales_wholesale = atoll(token);

        token = strtok(NULL, ",");
        if (!token)
        {
            fprintf(stderr, "Error: Malformed line %d (missing sales_retail)\n", line_number);
            line_number++;
            continue;
        }
        remove_quotes(token);
        e.sales_retail = atoll(token);

        token = strtok(NULL, ",");
        if (!token)
        {
            fprintf(stderr, "Error: Malformed line %d (missing sales_per_capita)\n", line_number);
            line_number++;
            continue;
        }
        remove_quotes(token);
        e.sales_per_capita = atoi(token);

        // Firms ownership
        token = strtok(NULL, ",");
        if (!token)
        {
            fprintf(stderr, "Error: Malformed line %d (missing firms_ai_owned)\n", line_number);
            line_number++;
            continue;
        }
        remove_quotes(token);
        e.firms_ai_owned = atoi(token);

        token = strtok(NULL, ",");
        if (!token)
        {
            fprintf(stderr, "Error: Malformed line %d (missing firms_asian_owned)\n", line_number);
            line_number++;
            continue;
        }
        remove_quotes(token);
        e.firms_asian_owned = atoi(token);

        token = strtok(NULL, ",");
        if (!token)
        {
            fprintf(stderr, "Error: Malformed line %d (missing firms_black_owned)\n", line_number);
            line_number++;
            continue;
        }
        remove_quotes(token);
        e.firms_black_owned = atoi(token);

        token = strtok(NULL, ",");
        if (!token)
        {
            fprintf(stderr, "Error: Malformed line %d (missing firms_hisp_owned)\n", line_number);
            line_number++;
            continue;
        }
        remove_quotes(token);
        e.firms_hisp_owned = atoi(token);

        token = strtok(NULL, ",");
        if (!token)
        {
            fprintf(stderr, "Error: Malformed line %d (missing firms_nh_pi_owned)\n", line_number);
            line_number++;
            continue;
        }
        remove_quotes(token);
        e.firms_nh_pi_owned = atoi(token);

        token = strtok(NULL, ",");
        if (!token)
        {
            fprintf(stderr, "Error: Malformed line %d (missing firms_total)\n", line_number);
            line_number++;
            continue;
        }
        remove_quotes(token);
        e.firms_total = atoi(token);

        token = strtok(NULL, ",");
        if (!token)
        {
            fprintf(stderr, "Error: Malformed line %d (missing firms_women_owned)\n", line_number);
            line_number++;
            continue;
        }
        remove_quotes(token);
        e.firms_women_owned = atoi(token);

        *entries = realloc(*entries, sizeof(struct entry) * (*count + 1));
        (*entries)[*count] = e;
        (*count)++;

        // printf("Parsed: County=%s, State=%s, 2014 Population=%u\n", e.county, e.state, e.pop_2014);

        line_number++;
    }

    fclose(file);
    return 1;
}

// OPERATION FILES HANDLING
void display(struct entry *entries, int count)
{
    for (int i = 0; i < count; i++)
    {
        printf("County: %s, State: %s, 2014 Population: %u\n",
               entries[i].county, entries[i].state, entries[i].pop_2014);

        // Age demographics
        printf("   Age 65+: %.2f, Age Under 18: %.2f, Age Under 5: %.2f\n",
               entries[i].age_65_plus, entries[i].age_under_18, entries[i].age_under_5);

        // Education
        printf("   Edu Bachelor's Plus: %.2f, Edu High School: %.2f\n",
               entries[i].edu_bachelor_plus, entries[i].edu_high_school);

        // Employment
        printf("   Nonemploy Est: %u, Private Emp: %u, Private Emp Chg: %.2f, Private Est: %u\n",
               entries[i].nonemploy_est, entries[i].private_emp, entries[i].private_emp_chg, entries[i].private_est);

        // Ethnicities
        printf("   Eth AI/AN: %.2f, Eth Asian: %.2f, Eth Black: %.2f, Eth Hispanic: %.2f, Eth NH/PI: %.2f, Eth Multi: %.2f, Eth White: %.2f, Eth White Non-Hispanic: %.2f\n",
               entries[i].eth_ai_an, entries[i].eth_asian, entries[i].eth_black, entries[i].eth_hispanic,
               entries[i].eth_nh_pi, entries[i].eth_multi, entries[i].eth_white, entries[i].eth_white_non_hisp);

        // Housing
        printf("   Homeown Rate: %.2f, Households: %u, Housing Units: %u, Median Home Value: %u, Persons per HH: %.2f, Multi-unit Struct: %.2f\n",
               entries[i].homeown_rate, entries[i].households, entries[i].housing_units, entries[i].median_home_val,
               entries[i].persons_per_hh, entries[i].multi_unit_struct);

        // Income
        printf("   Median Income: %u, Per Cap Income: %u, Poverty Rate: %.2f\n",
               entries[i].median_income, entries[i].per_cap_income, entries[i].poverty_rate);

        // Miscellaneous
        printf("   Building Permits: %u, Foreign Born: %.2f, Land Area: %.2f, Lang Non-English: %.2f, Same House 1 Yr: %.2f, Manuf Shipments: %llu, Mean Travel Time: %.2f, Percent Female: %.2f, Veterans: %u\n",
               entries[i].building_permits, entries[i].foreign_born, entries[i].land_area, entries[i].lang_non_english,
               entries[i].same_house_1yr, entries[i].manuf_shipments, entries[i].mean_travel_time, entries[i].percent_female,
               entries[i].veterans);

        // Population
        printf("   Population (2010): %u, Population (2014): %u, Population Chg: %.2f, Population Density: %.2f\n",
               entries[i].pop_2010, entries[i].pop_2014, entries[i].pop_chg, entries[i].pop_density);

        // Sales
        printf("   Sales Food & Accom: %llu, Sales Wholesale: %llu, Sales Retail: %llu, Sales Per Capita: %u\n",
               entries[i].sales_food_accom, entries[i].sales_wholesale, entries[i].sales_retail, entries[i].sales_per_capita);

        // Firms Ownership
        printf("   Firms AI Owned: %u, Firms Asian Owned: %u, Firms Black Owned: %u, Firms Hispanic Owned: %u, Firms NH/PI Owned: %u, Firms Total: %u, Firms Women Owned: %u\n",
               entries[i].firms_ai_owned, entries[i].firms_asian_owned, entries[i].firms_black_owned, entries[i].firms_hisp_owned,
               entries[i].firms_nh_pi_owned, entries[i].firms_total, entries[i].firms_women_owned);
    }
}

void filter_state(struct entry **entries, int *count, const char *state_abbr)
{
    int new_count = 0;
    for (int i = 0; i < *count; i++)
    {
        if (strncmp((*entries)[i].state, state_abbr, 2) == 0)
        {
            new_count++;
        }
    }

    struct entry *filtered_entries = malloc(sizeof(struct entry) * new_count);
    int j = 0;
    for (int i = 0; i < *count; i++)
    {
        if (strncmp((*entries)[i].state, state_abbr, 2) == 0)
        {
            filtered_entries[j++] = (*entries)[i];
        }
    }

    free(*entries);
    *entries = filtered_entries;
    *count = new_count;

    printf("Filter: state == %s (%d entries)\n", state_abbr, *count);
}

void filter(struct entry **entries, int *count, const char *field, const char *operator, float number)
{
    int new_count = 0;
    for (int i = 0; i < *count; i++)
    {
        float value = 0;
        int valid_field = 1;

        if (strcmp(field, "Age.Percent 65 and Older") == 0)
        {
            value = (*entries)[i].age_65_plus;
        }
        else if (strcmp(field, "Age.Percent Under 18 Years") == 0)
        {
            value = (*entries)[i].age_under_18;
        }
        else if (strcmp(field, "Age.Percent Under 5 Years") == 0)
        {
            value = (*entries)[i].age_under_5;
        }
        else if (strcmp(field, "Education.Bachelor's Degree or Higher") == 0)
        {
            value = (*entries)[i].edu_bachelor_plus;
        }
        else if (strcmp(field, "Education.High School or Higher") == 0)
        {
            value = (*entries)[i].edu_high_school;
        }
        else if (strcmp(field, "Ethnicities.American Indian and Alaska Native Alone") == 0)
        {
            value = (*entries)[i].eth_ai_an;
        }
        else if (strcmp(field, "Ethnicities.Asian Alone") == 0)
        {
            value = (*entries)[i].eth_asian;
        }
        else if (strcmp(field, "Ethnicities.Black Alone") == 0)
        {
            value = (*entries)[i].eth_black;
        }
        else if (strcmp(field, "Ethnicities.Hispanic or Latino") == 0)
        {
            value = (*entries)[i].eth_hispanic;
        }
        else if (strcmp(field, "Ethnicities.Native Hawaiian and Other Pacific Islander Alone") == 0)
        {
            value = (*entries)[i].eth_nh_pi;
        }
        else if (strcmp(field, "Ethnicities.Two or More Races") == 0)
        {
            value = (*entries)[i].eth_multi;
        }
        else if (strcmp(field, "Ethnicities.White Alone") == 0)
        {
            value = (*entries)[i].eth_white;
        }
        else if (strcmp(field, "Ethnicities.White Alone not Hispanic or Latino") == 0)
        {
            value = (*entries)[i].eth_white_non_hisp;
        }
        else if (strcmp(field, "Housing.Homeownership Rate") == 0)
        {
            value = (*entries)[i].homeown_rate;
        }
        else if (strcmp(field, "Housing.Persons per Household") == 0)
        {
            value = (*entries)[i].persons_per_hh;
        }
        else if (strcmp(field, "Housing.Units in Multi-Unit Structures") == 0)
        {
            value = (*entries)[i].multi_unit_struct;
        }
        else if (strcmp(field, "Income.Persons Below Poverty Level") == 0)
        {
            value = (*entries)[i].poverty_rate;
        }
        else if (strcmp(field, "Miscellaneous.Foreign Born") == 0)
        {
            value = (*entries)[i].foreign_born;
        }
        else if (strcmp(field, "Miscellaneous.Language Other than English at Home") == 0)
        {
            value = (*entries)[i].lang_non_english;
        }
        else if (strcmp(field, "Miscellaneous.Living in Same House +1 Years") == 0)
        {
            value = (*entries)[i].same_house_1yr;
        }
        else if (strcmp(field, "Miscellaneous.Mean Travel Time to Work") == 0)
        {
            value = (*entries)[i].mean_travel_time;
        }
        else if (strcmp(field, "Miscellaneous.Percent Female") == 0)
        {
            value = (*entries)[i].percent_female;
        }
        else if (strcmp(field, "Population.Population Percent Change") == 0)
        {
            value = (*entries)[i].pop_chg;
        }
        else if (strcmp(field, "Population.Population per Square Mile") == 0)
        {
            value = (*entries)[i].pop_density;
        }
        else
        {
            valid_field = 0;
        }

        if (valid_field)
        {
            int condition_met = 0;
            if (strcmp(operator, "ge") == 0 && value >= number)
            {
                condition_met = 1;
            }
            else if (strcmp(operator, "le") == 0 && value <= number)
            {
                condition_met = 1;
            }

            if (condition_met)
            {
                new_count++;
            }
        }
    }


    struct entry *filtered_entries = malloc(sizeof(struct entry) * new_count);
    int j = 0;
    for (int i = 0; i < *count; i++)
    {
        float value = 0;
        int valid_field = 1;

        if (strcmp(field, "Age.Percent 65 and Older") == 0)
        {
            value = (*entries)[i].age_65_plus;
        }
        else if (strcmp(field, "Age.Percent Under 18 Years") == 0)
        {
            value = (*entries)[i].age_under_18;
        }
        else if (strcmp(field, "Age.Percent Under 5 Years") == 0)
        {
            value = (*entries)[i].age_under_5;
        }
        else if (strcmp(field, "Education.Bachelor's Degree or Higher") == 0)
        {
            value = (*entries)[i].edu_bachelor_plus;
        }
        else if (strcmp(field, "Education.High School or Higher") == 0)
        {
            value = (*entries)[i].edu_high_school;
        }
        else if (strcmp(field, "Ethnicities.American Indian and Alaska Native Alone") == 0)
        {
            value = (*entries)[i].eth_ai_an;
        }
        else if (strcmp(field, "Ethnicities.Asian Alone") == 0)
        {
            value = (*entries)[i].eth_asian;
        }
        else if (strcmp(field, "Ethnicities.Black Alone") == 0)
        {
            value = (*entries)[i].eth_black;
        }
        else if (strcmp(field, "Ethnicities.Hispanic or Latino") == 0)
        {
            value = (*entries)[i].eth_hispanic;
        }
        else if (strcmp(field, "Ethnicities.Native Hawaiian and Other Pacific Islander Alone") == 0)
        {
            value = (*entries)[i].eth_nh_pi;
        }
        else if (strcmp(field, "Ethnicities.Two or More Races") == 0)
        {
            value = (*entries)[i].eth_multi;
        }
        else if (strcmp(field, "Ethnicities.White Alone") == 0)
        {
            value = (*entries)[i].eth_white;
        }
        else if (strcmp(field, "Ethnicities.White Alone not Hispanic or Latino") == 0)
        {
            value = (*entries)[i].eth_white_non_hisp;
        }
        else if (strcmp(field, "Housing.Homeownership Rate") == 0)
        {
            value = (*entries)[i].homeown_rate;
        }
        else if (strcmp(field, "Housing.Persons per Household") == 0)
        {
            value = (*entries)[i].persons_per_hh;
        }
        else if (strcmp(field, "Housing.Units in Multi-Unit Structures") == 0)
        {
            value = (*entries)[i].multi_unit_struct;
        }
        else if (strcmp(field, "Income.Persons Below Poverty Level") == 0)
        {
            value = (*entries)[i].poverty_rate;
        }
        else if (strcmp(field, "Miscellaneous.Foreign Born") == 0)
        {
            value = (*entries)[i].foreign_born;
        }
        else if (strcmp(field, "Miscellaneous.Language Other than English at Home") == 0)
        {
            value = (*entries)[i].lang_non_english;
        }
        else if (strcmp(field, "Miscellaneous.Living in Same House +1 Years") == 0)
        {
            value = (*entries)[i].same_house_1yr;
        }
        else if (strcmp(field, "Miscellaneous.Mean Travel Time to Work") == 0)
        {
            value = (*entries)[i].mean_travel_time;
        }
        else if (strcmp(field, "Miscellaneous.Percent Female") == 0)
        {
            value = (*entries)[i].percent_female;
        }
        else if (strcmp(field, "Population.Population Percent Change") == 0)
        {
            value = (*entries)[i].pop_chg;
        }
        else if (strcmp(field, "Population.Population per Square Mile") == 0)
        {
            value = (*entries)[i].pop_density;
        }
        else
        {
            valid_field = 0;
        }

        if (valid_field)
        {
            int condition_met = 0;
            if (strcmp(operator, "ge") == 0 && value >= number)
            {
                condition_met = 1;
            }
            else if (strcmp(operator, "le") == 0 && value <= number)
            {
                condition_met = 1;
            }

            if (condition_met)
            {
                filtered_entries[j++] = (*entries)[i];
            }
        }


    }

    //free(*entries);
    *entries = filtered_entries;
    *count = new_count;

    printf("Filter: %s %s %.2f (%d entries)\n", field, operator, number, *count);
}

void population_total(struct entry *entries, int count)
{
    unsigned int total_population = 0;
    for (int i = 0; i < count; i++)
    {
        total_population += entries[i].pop_2014;
    }
    printf("2014 population: %u\n", total_population);
}

void population(struct entry *entries, int count, const char *field)
{

    //printf("   field passed: '%s'\n", field);

    unsigned int total_sub_population = 0;
    for (int i = 0; i < count; i++)
    {
        float percentage = 0;

        if (strcmp(field, "Education.Bachelor's Degree or Higher\n") == 0)
        {
            percentage = entries[i].edu_bachelor_plus;
        }
        else if (strcmp(field, "Education.High School or Higher\n") == 0)
        {
            percentage = entries[i].edu_high_school;
        }
        else if (strcmp(field, "Ethnicities.American Indian and Alaska Native Alone\n") == 0)
        {
            percentage = entries[i].eth_ai_an;
        }
        else if (strcmp(field, "Ethnicities.Asian Alone\n") == 0)
        {
            percentage = entries[i].eth_asian;
        }
        else if (strcmp(field, "Ethnicities.Black Alone\n") == 0)
        {
            percentage = entries[i].eth_black;
        }
        else if (strcmp(field, "Ethnicities.Hispanic or Latino\n") == 0)
        {
            percentage = entries[i].eth_hispanic;
        }
        else if (strcmp(field, "Ethnicities.Native Hawaiian and Other Pacific Islander Alone\n") == 0)
        {
            percentage = entries[i].eth_nh_pi;
        }
        else if (strcmp(field, "Ethnicities.Two or More Races\n") == 0)
        {
            percentage = entries[i].eth_multi;
        }
        else if (strcmp(field, "Ethnicities.White Alone\n") == 0)
        {
            percentage = entries[i].eth_white;
        }
        else if (strcmp(field, "Ethnicities.White Alone, not Hispanic or Latino\n") == 0)
        {
            percentage = entries[i].eth_white_non_hisp;
        }
        else if (strcmp(field, "Income.Persons Below Poverty Level\n") == 0)
        {
            percentage = entries[i].poverty_rate;
        }
        else if (strcmp(field, "Housing.Homeownership Rate\n") == 0)
        {
            percentage = entries[i].homeown_rate;
        }
        else if (strcmp(field, "Housing.Persons per Household\n") == 0)
        {
            percentage = entries[i].persons_per_hh;
        }
        else if (strcmp(field, "Housing.Units in Multi-Unit Structures\n") == 0)
        {
            percentage = entries[i].multi_unit_struct;
        }
        else if (strcmp(field, "Miscellaneous.Foreign Born\n") == 0)
        {
            percentage = entries[i].foreign_born;
        }
        else if (strcmp(field, "Miscellaneous.Language Other than English at Home\n") == 0)
        {
            percentage = entries[i].lang_non_english;
        }
        else if (strcmp(field, "Miscellaneous.Living in Same House +1 Years\n") == 0)
        {
            percentage = entries[i].same_house_1yr;
        }

        total_sub_population += (unsigned int)(entries[i].pop_2014 * (percentage / 100));
    }

    printf("2014 %s population: %u\n", field, total_sub_population);
}

void percent(struct entry *entries, int count, const char *field)
{
    unsigned int total_population = 0;
    unsigned int total_sub_population = 0;

    for (int i = 0; i < count; i++)
    {
        total_population += entries[i].pop_2014;

        float percentage = 0;
        if (strcmp(field, "Education.Bachelor's Degree or Higher\n") == 0)
        {
            percentage = entries[i].edu_bachelor_plus;
        }
        else if (strcmp(field, "Education.High School or Higher\n") == 0)
        {
            percentage = entries[i].edu_high_school;
        }
        else if (strcmp(field, "Ethnicities.American Indian and Alaska Native Alone\n") == 0)
        {
            percentage = entries[i].eth_ai_an;
        }
        else if (strcmp(field, "Ethnicities.Asian Alone\n") == 0)
        {
            percentage = entries[i].eth_asian;
        }
        else if (strcmp(field, "Ethnicities.Black Alone\n") == 0)
        {
            percentage = entries[i].eth_black;
        }
        else if (strcmp(field, "Ethnicities.Hispanic or Latino\n") == 0)
        {
            percentage = entries[i].eth_hispanic;
        }
        else if (strcmp(field, "Ethnicities.Native Hawaiian and Other Pacific Islander Alone\n") == 0)
        {
            percentage = entries[i].eth_nh_pi;
        }
        else if (strcmp(field, "Ethnicities.Two or More Races\n") == 0)
        {
            percentage = entries[i].eth_multi;
        }
        else if (strcmp(field, "Ethnicities.White Alone\n") == 0)
        {
            percentage = entries[i].eth_white;
        }
        else if (strcmp(field, "Ethnicities.White Alone, not Hispanic or Latino\n") == 0)
        {
            percentage = entries[i].eth_white_non_hisp;
        }
        else if (strcmp(field, "Income.Persons Below Poverty Level\n") == 0)
        {
            percentage = entries[i].poverty_rate;
        }
        else if (strcmp(field, "Housing.Homeownership Rate\n") == 0)
        {
            percentage = entries[i].homeown_rate;
        }
        else if (strcmp(field, "Housing.Persons per Household\n") == 0)
        {
            percentage = entries[i].persons_per_hh;
        }
        else if (strcmp(field, "Housing.Units in Multi-Unit Structures\n") == 0)
        {
            percentage = entries[i].multi_unit_struct;
        }
        else if (strcmp(field, "Miscellaneous.Foreign Born\n") == 0)
        {
            percentage = entries[i].foreign_born;
        }
        else if (strcmp(field, "Miscellaneous.Language Other than English at Home\n") == 0)
        {
            percentage = entries[i].lang_non_english;
        }
        else if (strcmp(field, "Miscellaneous.Living in Same House +1 Years\n") == 0)
        {
            percentage = entries[i].same_house_1yr;
        }

        total_sub_population += (unsigned int)(entries[i].pop_2014 * (percentage / 100));
    }

    float percent = (total_population == 0) ? 0 : ((float)total_sub_population / total_population) * 100;
    printf("2014 %s percentage: %.2f%%\n", field, percent);
}

void operations(const char *operations_file, struct entry *entries, int *count)
{
    FILE *file = fopen(operations_file, "r");
    if (file == NULL)
    {
        perror("Error opening operations file");
        return;
    }

    char line[512];
    int line_number = 0;
    while (fgets(line, sizeof(line), file))
    {
        // printf("line: %s", line);
        line_number++;

        if (line[0] == '\n')
            continue;

        char operation[50];
        if (sscanf(line, "%s", operation) != 1)
        {
            fprintf(stderr, "Error on line %d: Invalid operation\n", line_number);
            continue;
        }

        if (strcmp(operation, "display") == 0)
        {
            display(entries, *count);
        }
        else if (strncmp(operation, "filter-state:", 13) == 0)
        {
            char state_abbr[3];
            sscanf(line + 13, "%2s", state_abbr);
            filter_state(&entries, count, state_abbr);
        }
        else if (strncmp(operation, "filter:", 7) == 0)
        {
            char field[256], operator[3];
            float number;
            if (sscanf(line + 7, "%[^:]:%2s:%f", field, operator, & number) == 3)
            {
                char temp[256];
                strcpy(temp, line + 7);

                printf("   field: '%s'\n", field);
                //printf("   operator: %s\n", operator);
                //printf("   number: %f\n", number);
                filter(&entries, count, field, operator, number);
            }
            else
            {
                fprintf(stderr, "Error on line %d: Malformed filter operation\n", line_number);
            }
        }
        else if (strcmp(operation, "population-total") == 0)
        {
            population_total(entries, *count);
        }
        else if (strncmp(operation, "population:", 11) == 0)
        {
            char *field;
            // printf("   line+11: %s\n", line + 11);
            field = line + 11;
            // printf("   field parsed: %s\n", field);
            population(entries, *count, field);
        }
        else if (strncmp(operation, "percent:", 8) == 0)
        {
            char *field;
            field = line + 8;
            //printf("   field passed: %s", field);
            percent(entries, *count, field);
        }
        else
        {
            fprintf(stderr, "Error on line %d: Unrecognized operation\n", line_number);
        }
    }

    fclose(file);
}

int file_exists(const char *filename)
{
    struct stat buffer;
    return (stat(filename, &buffer) == 0);
}

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        fprintf(stderr, "Usage: %s <data_file> <operations_file>\n", argv[0]);
        return 1; 
    }

    const char *data_file = argv[1];
    const char *operations_file = argv[2];

    if (!file_exists(data_file))
    {
        fprintf(stderr, "Error: Data file '%s' not found.\n", data_file);
        return 1; 
    }

    if (!file_exists(operations_file))
    {
        fprintf(stderr, "Error: Operations file '%s' not found.\n", operations_file);
        return 1; 
    }

    struct entry *entries = NULL;
    int count = 0;


    if (!load_data(data_file, &entries, &count))
    {
        return EXIT_FAILURE;
    }

    printf("Loaded %d entries successfully.\n", count);
    // display();
    printf("===============================================================\n");

    operations(operations_file, entries, &count);

    free(entries);
    printf("PROGRAM END\n");
    return 0;
}
