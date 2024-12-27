
//header
#ifndef HEADER_H
#define HEADER_H

struct vehicle
{
    char make[50];
    char model[50];
    char numberplate[20];
};

struct trip
{
    char startlocation[100];
    char endlocation[100];
    char date[20];
    char time[20];
    char status[20]; 
    char vehicle_make[50]; 
    char vehicle_model[50]; 
    int vehicle_available;
    char request_status[20];
    struct commuter *commuters[10]; 
    int numCommuters; 
};

struct commuter
{
    char name[50];
    char email[100];
    int mobile;
    double amount_due;
    char payment_status[20];
    struct trip *requested_trip;
};

struct feedback {
    char commenter_name[50];
    char comment[1000];
};

void addvehicle(struct vehicle **vehicles,int *numvehicles);
void deletevehicle(struct vehicle **vehicles,int *numvehicles);
void addtrip(struct trip **trips,int *numtrips);
void viewrequests(struct trip *trips,int numtrips);
void approverequest(struct trip *trips,int numtrips);
void rejectrequest(struct trip *trips,int numtrips);
void viewpasttrips(struct trip *trips,int numtrips);
void formtempgroups(struct vehicle *vehicles, int numvehicles, struct trip *trips, int numtrips, struct commuter *commuters, int numcommuters);
void calculatecost(struct trip *trips);
void viewpaymentstatus(struct commuter *commuters, int numcommuters);
void searchvehicles(struct vehicle *vehicles, int numvehicles);
void sendrequest(struct trip *trips, int numtrips, struct commuter *commuters, int numcommuters);
void makepayment(struct commuter *commuters, int numcommuters);
void viewupcomingtrips(struct trip *trips, int numtrips);
void viewvehicleavailability(struct trip *trips, int numtrips);
void givefeedback(struct feedback **feedbacks, int *num_feedbacks);

#endif

//main
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "header.h"
int isFutureDate(const char *date);
int main()
{
    struct vehicle *vehicles = NULL;
    int numvehicles=0;
    struct trip *trips = NULL;
    int numtrips=0;
    struct commuter *commuters = NULL;
    int numcommuters=0;
    struct feedback *feedbacks = NULL;
    int num_feedbacks=0;
    
    vehicles = (struct vehicle*)malloc(sizeof(struct vehicle));
    trips = (struct trip*)malloc(sizeof(struct trip));
    commuters = (struct commuter*)malloc(sizeof(struct commuter));
    feedbacks = (struct feedback*)malloc(sizeof(struct feedback));
    int choice;
    if (vehicles == NULL || trips == NULL || commuters == NULL || feedbacks == NULL)
    {
        printf("Memory allocation failed. Exiting...\n");
        return 1;
    }

    do {
        // Display menu
        printf("\nMenu:\n");
        printf("1. Add Vehicle\n");
        printf("2. Delete Vehicle\n");
        printf("3. Add Trip\n");
        printf("4. View Requests\n");
        printf("5. Approve Request\n");
        printf("6. Reject Request\n");
        printf("7. View Past Trips\n");
        printf("8. Form Temporary Groups\n");
        printf("9. Calculate Cost\n");
        printf("10. View Payment Status\n");
        printf("11. Search Vehicles\n");
        printf("12. Send Request\n");
        printf("13. View Upcoming Trips\n");
        printf("14. Make Payment\n");
        printf("15. View Vehicle Availability\n");
        printf("16. Give Feedback\n");
        printf("17. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        // Process user choice
        switch(choice) {
            case 1:
                addvehicle(&vehicles, &numvehicles);
                break;
            case 2:
                deletevehicle(&vehicles, &numvehicles);
                break;
            case 3:
                addtrip(&trips, &numtrips);
                break;
            case 4:
                viewrequests(trips, numtrips);
                break;
            case 5:
                approverequest(trips, numtrips);
                break;
            case 6:
                rejectrequest(trips, numtrips);
                break;
            case 7:
                viewpasttrips(trips, numtrips);
                break;
            case 8:
                formtempgroups(vehicles, numvehicles, trips, numtrips, commuters, numcommuters);
                break;
            case 9:
                calculatecost(trips);
                break;
            case 10:
                viewpaymentstatus(commuters, numcommuters);
                break;
            case 11:
                searchvehicles(vehicles, numvehicles);
                break;
            case 12:
                sendrequest(trips, numtrips, commuters, numcommuters);
                break;
            case 13:
                viewupcomingtrips(trips, numtrips);
                break;
            case 14:
                makepayment(commuters, numcommuters);
                break;
            case 15:
                viewvehicleavailability(trips, numtrips);
                break;
            case 16:
                givefeedback(&feedbacks, &num_feedbacks);
                break;
            case 17:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice. Please enter a number between 1 and 17.\n");
        }
    } while(choice != 17);

    

   free(vehicles);
   vehicles = NULL;

   free(trips);
   trips = NULL;

   free(commuters);
   commuters = NULL;

   free(feedbacks);
   feedbacks = NULL;


    return 0;
}

void addvehicle(struct vehicle **vehicles, int *numvehicles) {
    (*numvehicles)++;
    *vehicles = realloc(*vehicles, sizeof(struct vehicle) * (*numvehicles));
    if (*vehicles == NULL) {
        printf("Memory allocation failed. Exiting...\n");
        exit(1);
    }

    printf("Enter vehicle details:\n");
    printf("Make: ");
    scanf("%s", (*vehicles)[*numvehicles - 1].make);
    printf("Model: ");
    scanf("%s", (*vehicles)[*numvehicles - 1].model);
    printf("Number Plate: ");
    scanf("%s", (*vehicles)[*numvehicles - 1].numberplate);
}

void deletevehicle(struct vehicle **vehicles, int *numvehicles) {
    char plateToDelete[20];
    printf("Enter the number plate of the vehicle to delete: ");
    scanf("%s", plateToDelete);

    int found = 0;
    for (int i = 0; i < *numvehicles; i++) {
        if (strcmp((*vehicles)[i].numberplate, plateToDelete) == 0) {
            for (int j = i; j < *numvehicles - 1; j++) {
                (*vehicles)[j] = (*vehicles)[j + 1];
            }
            (*numvehicles)--;
            found = 1;
            break;
        }
    }

    if (found) {
        printf("Vehicle with number plate %s deleted.\n", plateToDelete);
    } else {
        printf("Vehicle with number plate %s not found.\n", plateToDelete);
    }
}


void addtrip(struct trip **trips, int *numtrips) {
    (*numtrips)++;
    *trips = realloc(*trips, sizeof(struct trip) * (*numtrips));
    if (*trips == NULL) {
        printf("Memory allocation failed. Unable to add trip.\n");
        return;
    }
    printf("Enter start location of the trip:");
    scanf("%s", (*trips)[*numtrips - 1].startlocation);
    printf("Enter end location of the trip:");
    scanf("%s", (*trips)[*numtrips - 1].endlocation);
    printf("Enter date of the trip:");
    scanf("%s", (*trips)[*numtrips - 1].date);
    printf("Enter time of the trip:");
    scanf("%s", (*trips)[*numtrips - 1].time);
    printf("Trip added successfully.\n");
}

void viewrequests(struct trip *trips, int numtrips) {
    printf("List of trip requests:\n");
    for (int i = 0; i < numtrips; i++) {
        if (strcmp(trips[i].status, "request") == 0) {
            printf("Trip %d:\n", i + 1);
            printf("Start Location: %s\n", trips[i].startlocation);
            printf("End Location: %s\n", trips[i].endlocation);
            printf("Date: %s\n", trips[i].date);
            printf("Time: %s\n", trips[i].time);
            printf("\n");
        }
    }
}

void approverequest(struct trip *trips, int numtrips) {
    char response[10];
    printf("Enter the trip number to approve: ");
    int trip_number;
    scanf("%d", &trip_number);
    if (trip_number < 1 || trip_number > numtrips) {
        printf("Invalid trip number.\n");
        return;
    }

    printf("Are you sure you want to approve this trip? (yes/no): ");
    scanf("%s", response);
    if (strcmp(response, "yes") == 0) {
        // Mark the trip as approved
        strcpy(trips[trip_number - 1].status, "approved");
        printf("Trip %d approved successfully.\n", trip_number);
    } else {
        printf("Approval canceled.\n");
    }
}

 void rejectrequest(struct trip *trips, int numtrips) {
    char response[10];
    printf("Enter the trip number to reject: ");
    int trip_number;
    scanf("%d", &trip_number);
    if (trip_number < 1 || trip_number > numtrips) {
        printf("Invalid trip number.\n");
        return;
    }

    printf("Are you sure you want to reject this trip? (yes/no): ");
    scanf("%s", response);
    if (strcmp(response, "yes") == 0) {
        strcpy(trips[trip_number - 1].status, "rejected");
        printf("Trip %d rejected successfully.\n", trip_number);
    } else {
        printf("Rejection canceled.\n");
    }
}

void viewpasttrips(struct trip *trips, int numtrips) {
    printf("List of past trips:\n");
    for (int i = 0; i < numtrips; i++) {
        if (strcmp(trips[i].status, "past") == 0) {
            printf("Trip %d:\n", i + 1);
            printf("Start Location: %s\n", trips[i].startlocation);
            printf("End Location: %s\n", trips[i].endlocation);
            printf("Date: %s\n", trips[i].date);
            printf("Time: %s\n", trips[i].time);
            printf("\n");
        }
    }
}

void formtempgroups(struct vehicle *vehicles, int numvehicles, struct trip *trips, int numtrips, struct commuter *commuters, int numcommuters) {
    printf("Available Vehicles:\n");
    for (int i = 0; i < numvehicles; i++) {
        printf("Vehicle %d: %s %s\n", i + 1, vehicles[i].make, vehicles[i].model);
    }
    printf("\n");

    printf("Available Trips:\n");
    for (int i = 0; i < numtrips; i++) {
        printf("Trip %d: %s to %s\n", i + 1, trips[i].startlocation, trips[i].endlocation);
    }
    printf("\n");

    printf("Commuters forming groups:\n");
    for (int i = 0; i < numcommuters; i++) {
        printf("Commuter %d (%s):\n", i + 1, commuters[i].name);

        int vehicle_choice;
        printf("Select a vehicle (1-%d): ", numvehicles);
        scanf("%d", &vehicle_choice);
        if (vehicle_choice < 1 || vehicle_choice > numvehicles) {
            printf("Invalid vehicle choice.\n");
            continue;
        }

        char permission;
        printf("Does the owner give permission to join this group? (y/n): ");
        scanf(" %c", &permission);
        if (permission != 'y' && permission != 'Y') {
            printf("Owner did not give permission to join this group.\n");
            continue;
        }

        int trip_choice;
        printf("Select a trip (1-%d): ", numtrips);
        scanf("%d", &trip_choice);
        if (trip_choice < 1 || trip_choice > numtrips) {
            printf("Invalid trip choice.\n");
            continue;
        }

        printf("Chosen vehicle: %s %s\n", vehicles[vehicle_choice - 1].make, vehicles[vehicle_choice - 1].model);
        printf("Chosen trip: %s to %s\n", trips[trip_choice - 1].startlocation, trips[trip_choice - 1].endlocation);

        printf("Commuter added to the group.\n");

        trips[trip_choice - 1].commuters[trips[trip_choice - 1].numCommuters] = &commuters[i];
        trips[trip_choice - 1].numCommuters++;

        printf("\n");
    }
}

void calculatecost(struct trip *trips)
{
    double fuel_cost_per_unit = 2.5; 
    double fuel_consumption_rate = 0.15; 

    double distance;
    double fuel_consumed;
    double cost;

    distance = 100.0;
    fuel_consumed = fuel_consumption_rate * distance;
    cost = fuel_consumed * fuel_cost_per_unit;

    printf("Cost for the trip: $%.2f\n", cost);
}

void viewpaymentstatus(struct commuter *commuters, int numcommuters) {
    printf("Payment Status:\n");
    for (int i = 0; i < numcommuters; i++) {
        printf("Commuter %d: %s - Payment Status: %s\n", i + 1, commuters[i].name, commuters[i].payment_status);
    }
}

void searchvehicles(struct vehicle *vehicles, int numvehicles ) {
    int found = 0;
    const char search_term[100];
    printf("Search Results for \"%s\":\n");
    scanf(search_term);
    for (int i = 0; i < numvehicles; i++) {
        if (strstr(vehicles[i].make, search_term) != NULL || strstr(vehicles[i].model, search_term) != NULL || strstr(vehicles[i].numberplate, search_term) != NULL) {
            printf("Vehicle %d: Make: %s, Model: %s, Number Plate: %s\n", i + 1, vehicles[i].make, vehicles[i].model, vehicles[i].numberplate);
            found = 1;
        }
    }

    if (!found) {
        printf("No vehicles matching \"%s\" found.\n", search_term);
    }
}
void sendrequest(struct trip *trips, int numtrips, struct commuter *commuters, int numcommuters) {
    int trip_number;
    printf("Available Trips:\n");
    for (int i = 0; i < numtrips; i++) {
        printf("Trip %d: %s to %s\n", i + 1, trips[i].startlocation, trips[i].endlocation);
    }

    printf("Enter the trip number to send request: ");
    scanf("%d", &trip_number);
    if (trip_number < 1 || trip_number > numtrips) {
        printf("Invalid trip number.\n");
        return;
    }

    printf("Request sent for trip %d: %s to %s\n", trip_number, trips[trip_number - 1].startlocation, trips[trip_number - 1].endlocation);

    strcpy(trips[trip_number - 1].request_status, "Pending");

    commuters->requested_trip = &trips[trip_number - 1];
}

void viewupcomingtrips(struct trip *trips, int numtrips)
{

 printf("Upcoming Trips:\n");
    int upcoming_trip_count = 0;
    for (int i = 0; i < numtrips; i++) {
        if (isFutureDate(trips[i].date) && (strcmp(trips[i].status, "request") == 0 || strcmp(trips[i].status, "approved") == 0)) {
            printf("Trip %d:\n", i + 1);
            printf("Start Location: %s\n", trips[i].startlocation);
            printf("End Location: %s\n", trips[i].endlocation);
            printf("Date: %s\n", trips[i].date);
            printf("Time: %s\n", trips[i].time);
            printf("\n");
            upcoming_trip_count++;
        }
    }
    if (upcoming_trip_count == 0) {
        printf("No upcoming trips found.\n");
    }
}
int isFutureDate(const char *date) {
    struct tm given_time = {0};
    time_t current_time = time(NULL);
    struct tm *current_local_time = localtime(&current_time);

  
    sscanf(date, "%d-%d-%d", &given_time.tm_year, &given_time.tm_mon, &given_time.tm_mday);
    given_time.tm_year -= 1900; 
    given_time.tm_mon--; 

    if (mktime(&given_time) > mktime(current_local_time)) {
        return 1;
    } else {
        return 0; 
    }
}

void makepayment(struct commuter *commuters, int numcommuters) {
    int commuter_index;
    double payment_amount;

    printf("Enter your name: ");
    char name[50];
    scanf("%s", name);
    for (int i = 0; i < numcommuters; i++) {
        if (strcmp(commuters[i].name, name) == 0) {
            commuter_index = i;
            break;
        }
    }

    if (strcmp(commuters[commuter_index].name, name) != 0) {
        printf("Commuter not found.\n");
        return;
    }

    printf("Amount due: $%.2f\n", commuters[commuter_index].amount_due);
    printf("Enter payment amount: $");
    scanf("%lf", &payment_amount);

    if (payment_amount <= 0) {
        printf("Invalid payment amount.\n");
        return;
    }

    commuters[commuter_index].amount_due -= payment_amount;
    if (commuters[commuter_index].amount_due <= 0) {
        strcpy(commuters[commuter_index].payment_status, "Paid");
    }

    printf("Payment successful. Remaining amount due: $%.2f\n", commuters[commuter_index].amount_due);
}

void viewvehicleavailability(struct trip *trips, int numtrips) {
    printf("Vehicle availability:\n");
    for (int i = 0; i < numtrips; i++) {
        printf("Trip %d: %s to %s - Vehicle: %s %s - Availability: %s\n", i + 1, trips[i].startlocation, trips[i].endlocation, trips[i].vehicle_make, trips[i].vehicle_model, trips[i].vehicle_available ? "Available" : "Unavailable");
    }
}

void givefeedback(struct feedback **feedbacks, int *num_feedbacks) {
    (*num_feedbacks)++;
    *feedbacks = realloc(*feedbacks, sizeof(struct feedback) * (*num_feedbacks));
    if (*feedbacks == NULL) {
        printf("Memory allocation failed. Exiting...\n");
        exit(1);
    }

    printf("Enter your name: ");
    scanf("%s", (*feedbacks)[*num_feedbacks - 1].commenter_name);

    printf("Enter your feedback (max 1000 characters):\n");
    scanf(" %[^\n]", (*feedbacks)[*num_feedbacks - 1].comment);

    printf("Thank you for your feedback!\n");
}
