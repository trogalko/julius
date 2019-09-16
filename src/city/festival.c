#include "festival.h"

#include "building/warehouse.h"
#include "city/constants.h"
#include "city/data_private.h"
#include "city/finance.h"
#include "city/message.h"
#include "city/sentiment.h"

int city_festival_is_planned(void)
{
    return city_data.festival.planned.size != FESTIVAL_NONE;
}

int city_festival_months_since_last(void)
{
    return city_data.festival.months_since_festival;
}

int city_festival_small_cost(void)
{
    return city_data.festival.small_cost;
}

int city_festival_large_cost(void)
{
    return city_data.festival.large_cost;
}

int city_festival_grand_cost(void)
{
    return city_data.festival.grand_cost;
}

int city_festival_grand_wine(void)
{
    return city_data.festival.grand_wine;
}

int city_festival_out_of_wine(void)
{
    return city_data.festival.not_enough_wine;
}

int city_festival_selected_god(void)
{
    return city_data.festival.selected.god;
}

void city_festival_select_god(int god_id)
{
    city_data.festival.selected.god = god_id;
}

int city_festival_selected_size(void)
{
    return city_data.festival.selected.size;
}

int city_festival_select_size(int size)
{
    if (size == FESTIVAL_GRAND && city_data.festival.not_enough_wine) {
        return 0;
    }
    city_data.festival.selected.size = size;
    return 1;
}

void city_festival_schedule(void)
{
    city_data.festival.planned.god = city_data.festival.selected.god;
    city_data.festival.planned.size = city_data.festival.selected.size;
    int cost;
    if (city_data.festival.selected.size == FESTIVAL_SMALL) {
        city_data.festival.planned.months_to_go = 2;
        cost = city_data.festival.small_cost;
    } else if (city_data.festival.selected.size == FESTIVAL_LARGE) {
        city_data.festival.planned.months_to_go = 3;
        cost = city_data.festival.large_cost;
    } else {
        city_data.festival.planned.months_to_go = 2;
        //cost = city_data.festival.grand_cost;
        cost = city_data.festival.small_cost;
    }

    city_finance_process_sundry(cost);

    //if (city_data.festival.selected.size == FESTIVAL_GRAND) {
    //    building_warehouses_remove_resource(RESOURCE_WINE, city_data.festival.grand_wine);
    //}
}

static void throw_party(void)
{
    if (city_data.festival.first_festival_effect_months <= 0) {
        city_data.festival.first_festival_effect_months = 12;
        switch (city_data.festival.planned.size) {
            case FESTIVAL_SMALL: city_sentiment_change_happiness(7); break;
            case FESTIVAL_LARGE: city_sentiment_change_happiness(9); break;
            case FESTIVAL_GRAND: city_sentiment_change_happiness(12); break;
        }
    } else if (city_data.festival.second_festival_effect_months <= 0) {
        city_data.festival.second_festival_effect_months = 12;
        switch (city_data.festival.planned.size) {
            case FESTIVAL_SMALL: city_sentiment_change_happiness(2); break;
            case FESTIVAL_LARGE: city_sentiment_change_happiness(3); break;
            case FESTIVAL_GRAND: city_sentiment_change_happiness(5); break;
        }
    }
    city_data.festival.months_since_festival = 1;
    city_data.religion.gods[city_data.festival.planned.god].months_since_festival = 0;
    switch (city_data.festival.planned.size) {
        case FESTIVAL_SMALL: city_message_post(1, MESSAGE_SMALL_FESTIVAL, 0, 0); break;
        case FESTIVAL_LARGE: city_message_post(1, MESSAGE_LARGE_FESTIVAL, 0, 0); break;
        case FESTIVAL_GRAND: city_message_post(1, MESSAGE_GRAND_FESTIVAL, 0, 0); break;
    }
    city_data.festival.planned.size = FESTIVAL_NONE;
    city_data.festival.planned.months_to_go = 0;
}

void city_festival_update(void)
{
    city_data.festival.months_since_festival++;
    if (city_data.festival.first_festival_effect_months) {
        --city_data.festival.first_festival_effect_months;
    }
    if (city_data.festival.second_festival_effect_months) {
        --city_data.festival.second_festival_effect_months;
    }
    if (city_festival_is_planned()) {
        city_data.festival.planned.months_to_go--;
        if (city_data.festival.planned.months_to_go <= 0) {
            throw_party();
        }
    }
}

void city_festival_calculate_costs(void)
{
    city_data.festival.small_cost = city_data.population.population / 20 + 10;
    city_data.festival.large_cost = city_data.population.population / 10 + 20;
    city_data.festival.grand_cost = city_data.population.population / 5 + 40;
    city_data.festival.grand_wine = city_data.population.population / 500 + 1;
    city_data.festival.not_enough_wine = 0;
    if (city_data.resource.stored_in_warehouses[RESOURCE_WINE] < city_data.festival.grand_wine) {
        city_data.festival.not_enough_wine = 1;
        if (city_data.festival.selected.size == FESTIVAL_GRAND) {
            city_data.festival.selected.size = FESTIVAL_LARGE;
        }
    }
}
