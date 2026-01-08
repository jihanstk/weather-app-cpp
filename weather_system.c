// /*
//  * ============================================================
//  * WEATHER FORECASTING SYSTEM - BEGINNER VERSION
//  * ============================================================
//  * Course: Software Development – I (CSE 1290)
//  * Department of CSE
//  * 
//  * This simplified version demonstrates:
//  * - while loops
//  * - if-else conditions
//  * - functions
//  * - user input/output
//  * ============================================================
//  */

// #include <stdio.h>      // For printf, scanf, fgets
// #include <stdlib.h>     // For exit, atof
// #include <string.h>     // For strlen, strcpy, strstr
// #include <curl/curl.h>  // For API calls

// // ============================================================
// // CONFIGURATION - Put your API key here!
// // ============================================================
// #define API_KEY "c8b4128ba2cb1a2c6ad45780d2fbcc6a"

// // ============================================================
// // STRUCTURE to store weather data
// // ============================================================
// struct WeatherInfo {
//     char city[100];
//     char country[10];
//     double temperature;
//     double feels_like;
//     int humidity;
//     double wind_speed;
//     char condition[50];
//     char description[100];
// };

// // ============================================================
// // GLOBAL VARIABLES for API response
// // ============================================================
// char api_response[5000];
// int response_length = 0;

// // ============================================================
// // FUNCTION DECLARATIONS
// // ============================================================
// void print_header(void);
// void print_menu(void);
// void get_weather(char city[]);
// void display_weather(struct WeatherInfo weather);
// void show_weather_alert(struct WeatherInfo weather);
// double find_number(char *text, char *key);
// void find_text(char *text, char *key, char *result);

// // ============================================================
// // CALLBACK FUNCTION for curl - saves API response
// // ============================================================
// size_t handle_response(void *data, size_t size, size_t count, void *unused) {
//     (void)unused;  // Avoid unused parameter warning
//     int total = size * count;
//     int i;
    
//     for (i = 0; i < total; i++) {
//         if (response_length < 4999) {
//             api_response[response_length] = ((char*)data)[i];
//             response_length = response_length + 1;
//         }
//     }
//     api_response[response_length] = '\0';
    
//     return total;
// }

// // ============================================================
// // MAIN FUNCTION - Program starts here!
// // ============================================================
// int main(void) {
//     int choice;
//     char city[100];
//     int running = 1;
    
//     // Initialize curl library
//     curl_global_init(CURL_GLOBAL_DEFAULT);
    
//     // ========================================================
//     // MAIN WHILE LOOP - Keeps running until user exits
//     // ========================================================
//     while (running == 1) {
        
//         print_header();
//         print_menu();
        
//         printf("  Enter your choice: ");
        
//         // IF condition to check valid input
//         if (scanf("%d", &choice) != 1) {
//             while (getchar() != '\n');
//             printf("\n  ERROR: Please enter a number!\n");
//             printf("\n  Press Enter to continue...");
//             getchar();
//             continue;
//         }
        
//         while (getchar() != '\n');
        
//         // ====================================================
//         // IF-ELSE CONDITIONS for menu choices
//         // ====================================================
//         if (choice == 1) {
//             // Get weather option
//             printf("\n  Enter city name: ");
//             fgets(city, sizeof(city), stdin);
            
//             // Remove newline using a while loop
//             int i = 0;
//             while (city[i] != '\0') {
//                 if (city[i] == '\n') {
//                     city[i] = '\0';
//                     break;
//                 }
//                 i = i + 1;
//             }
            
//             // IF-ELSE to check empty city
//             if (strlen(city) == 0) {
//                 printf("\n  ERROR: City name cannot be empty!\n");
//             } else {
//                 get_weather(city);
//             }
            
//             printf("\n  Press Enter to continue...");
//             getchar();
            
//         } else if (choice == 2) {
//             // Exit option
//             printf("\n  Thank you for using Weather System!\n");
//             printf("  Goodbye!\n\n");
//             running = 0;
            
//         } else {
//             // Invalid choice
//             printf("\n  ERROR: Invalid choice! Please enter 1 or 2.\n");
//             printf("\n  Press Enter to continue...");
//             getchar();
//         }
        
//     }
    
//     curl_global_cleanup();
//     return 0;
// }

// // ============================================================
// // FUNCTION: Print header
// // ============================================================
// void print_header(void) {
//     printf("\n");
//     printf("========================================================\n");
//     printf("          WEATHER FORECASTING SYSTEM                    \n");
//     printf("          Department of CSE - CSE 1290                 \n");
//     printf("========================================================\n");
//     printf("\n");
// }

// // ============================================================
// // FUNCTION: Print menu
// // ============================================================
// void print_menu(void) {
//     printf("  MENU:\n");
//     printf("  --------------------------------------------------------\n");
//     printf("  1. Get Current Weather\n");
//     printf("  2. Exit Program\n");
//     printf("  --------------------------------------------------------\n\n");
// }

// // ============================================================
// // FUNCTION: Find a number in JSON
// // ============================================================
// double find_number(char *text, char *key) {
//     char search[100];
//     char *position;
    
//     sprintf(search, "\"%s\":", key);
//     position = strstr(text, search);
    
//     if (position == NULL) {
//         return 0.0;
//     }
    
//     position = position + strlen(search);
//     return atof(position);
// }

// // ============================================================
// // FUNCTION: Find text in JSON
// // ============================================================
// void find_text(char *text, char *key, char *result) {
//     char search[100];
//     char *start;
//     char *end;
//     int i;
    
//     sprintf(search, "\"%s\":\"", key);
//     start = strstr(text, search);
    
//     if (start == NULL) {
//         result[0] = '\0';
//         return;
//     }
    
//     start = start + strlen(search);
//     end = start;
    
//     // While loop to find end quote
//     while (*end != '"' && *end != '\0') {
//         end = end + 1;
//     }
    
//     // For loop to copy text
//     for (i = 0; i < (end - start) && i < 99; i++) {
//         result[i] = start[i];
//     }
//     result[i] = '\0';
// }

// // ============================================================
// // FUNCTION: Get weather from API
// // ============================================================
// void get_weather(char city[]) {
//     CURL *curl;
//     CURLcode result;
//     char url[500];
//     struct WeatherInfo weather;
    
//     printf("\n  Fetching weather data...\n");
    
//     response_length = 0;
//     api_response[0] = '\0';
    
//     sprintf(url, 
//         "https://api.openweathermap.org/data/2.5/weather?q=%s&appid=%s&units=metric",
//         city, API_KEY);
    
//     curl = curl_easy_init();
    
//     if (curl == NULL) {
//         printf("  ERROR: Could not connect!\n");
//         return;
//     }
    
//     curl_easy_setopt(curl, CURLOPT_URL, url);
//     curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, handle_response);
//     curl_easy_setopt(curl, CURLOPT_TIMEOUT, 10L);
    
//     result = curl_easy_perform(curl);
    
//     // IF condition to check connection
//     if (result != CURLE_OK) {
//         printf("  ERROR: Check internet connection.\n");
//         curl_easy_cleanup(curl);
//         return;
//     }
    
//     curl_easy_cleanup(curl);
    
//     // IF condition to check if city exists
//     if (strstr(api_response, "\"cod\":\"404\"") != NULL) {
//         printf("\n  ERROR: City not found!\n");
//         return;
//     }
    
//     // Extract weather data
//     find_text(api_response, "name", weather.city);
//     find_text(api_response, "country", weather.country);
//     weather.temperature = find_number(api_response, "temp");
//     weather.feels_like = find_number(api_response, "feels_like");
//     weather.humidity = (int)find_number(api_response, "humidity");
//     weather.wind_speed = find_number(api_response, "speed");
//     find_text(api_response, "main", weather.condition);
//     find_text(api_response, "description", weather.description);
    
//     display_weather(weather);
//     show_weather_alert(weather);
// }

// // ============================================================
// // FUNCTION: Display weather
// // ============================================================
// void display_weather(struct WeatherInfo weather) {
//     printf("\n");
//     printf("  ========================================================\n");
//     printf("  WEATHER REPORT\n");
//     printf("  ========================================================\n");
//     printf("  Location:      %s, %s\n", weather.city, weather.country);
//     printf("  --------------------------------------------------------\n");
//     printf("  Temperature:   %.1f C\n", weather.temperature);
//     printf("  Feels Like:    %.1f C\n", weather.feels_like);
//     printf("  Humidity:      %d%%\n", weather.humidity);
//     printf("  Wind Speed:    %.1f m/s\n", weather.wind_speed);
//     printf("  Condition:     %s\n", weather.condition);
//     printf("  Description:   %s\n", weather.description);
//     printf("  --------------------------------------------------------\n");
// }

// // ============================================================
// // FUNCTION: Show weather alert using IF-ELSE IF-ELSE
// // ============================================================
// void show_weather_alert(struct WeatherInfo weather) {
//     printf("\n  WEATHER ALERT: ");
    
//     // IF-ELSE IF-ELSE chain
//     if (strstr(weather.condition, "Rain") != NULL) {
//         printf("It's raining! Take an umbrella!\n");
//     }
//     else if (strstr(weather.condition, "Thunderstorm") != NULL) {
//         printf("Thunderstorm! Stay indoors!\n");
//     }
//     else if (strstr(weather.condition, "Snow") != NULL) {
//         printf("It's snowing! Dress warmly!\n");
//     }
//     else if (weather.temperature > 35) {
//         printf("Heat warning! Stay hydrated!\n");
//     }
//     else if (weather.temperature < 5) {
//         printf("Cold warning! Dress warmly!\n");
//     }
//     else if (strstr(weather.condition, "Clear") != NULL) {
//         printf("Clear skies! Great day!\n");
//     }
//     else if (strstr(weather.condition, "Clouds") != NULL) {
//         printf("Cloudy weather!\n");
//     }
//     else {
//         printf("Have a great day!\n");
//     }
    
//     printf("  ========================================================\n");
// }



























// #include <stdio.h>      // Lets us use printf (to show text) and scanf (to get input)
// #include <stdlib.h>     // Lets us use exit and convert text to numbers
// #include <string.h>     // Lets us work with text (strings)
// #include <curl/curl.h>  // Lets us get data from the internet

// // ============================================================
// // YOUR API KEY - This is like a password to access weather data
// // ============================================================
// #define API_KEY "c8b4128ba2cb1a2c6ad45780d2fbcc6a"

// // ============================================================
// // A "box" to store weather information
// // Think of this like a form with different fields to fill out
// // ============================================================
// struct WeatherInfo {
//     char city[100];           // Name of the city (like "Dhaka")
//     char country[10];         // Country code (like "BD")
//     double temperature;       // Temperature in Celsius
//     double feels_like;        // What temperature feels like
//     int humidity;             // Humidity percentage
//     double wind_speed;        // Wind speed in meters/second
//     char condition[50];       // Main condition (like "Rain" or "Clear")
//     char description[100];    // Detailed description
// };

// // ============================================================
// // Storage space for data we get from the internet
// // ============================================================
// char internet_data[5000];     // Big space to store the weather data
// int data_size = 0;            // How much data we've stored

// // ============================================================
// // List of all our helper functions (small programs)
// // We list them here so the computer knows they exist
// // ============================================================
// void show_title(void);
// void show_menu(void);
// void get_weather_data(char city_name[]);
// void show_weather_report(struct WeatherInfo weather);
// void show_weather_tips(struct WeatherInfo weather);
// double get_number_from_data(char *data, char *what_to_find);
// void get_text_from_data(char *data, char *what_to_find, char *where_to_save);

// // ============================================================
// // Special function that saves data from the internet
// // Don't worry too much about how this works - it's automatic!
// // ============================================================
// size_t save_internet_data(void *new_data, size_t size, size_t count, void *unused) {
//     (void)unused;  // We don't use this, but we need it here
    
//     // Calculate how many characters we got
//     int total_characters = size * count;
//     int i;
    
//     // Copy each character one by one
//     for (i = 0; i < total_characters; i++) {
//         if (data_size < 4999) {  // Make sure we don't overflow our storage
//             internet_data[data_size] = ((char*)new_data)[i];
//             data_size = data_size + 1;
//         }
//     }
    
//     // Add end marker
//     internet_data[data_size] = '\0';
    
//     return total_characters;
// }

// // ============================================================
// // MAIN FUNCTION - This is where our program starts!
// // ============================================================
// int main(void) {
//     // Variables we need
//     int user_choice;              // Stores what option user picks
//     char city_name[100];          // Stores the city name user types
//     int keep_running = 1;         // 1 means "yes, keep running", 0 means "stop"
    
//     // Start the internet connection system
//     curl_global_init(CURL_GLOBAL_DEFAULT);
    
//     // ========================================================
//     // MAIN LOOP - This keeps the program running
//     // The program will keep showing the menu until user exits
//     // ========================================================
//     while (keep_running == 1) {
        
//         // Show the title and menu
//         show_title();
//         show_menu();
        
//         // Ask user what they want to do
//         printf("  What would you like to do? Enter 1 or 2: ");
        
//         // Try to read the user's choice
//         // scanf returns 1 if it successfully reads a number
//         if (scanf("%d", &user_choice) != 1) {
//             // Oops! User didn't enter a number
//             // Clear the bad input
//             while (getchar() != '\n');
            
//             printf("\n  OOPS! Please enter a number (1 or 2)!\n");
//             printf("\n  Press Enter to try again...");
//             getchar();
//             continue;  // Go back to start of while loop
//         }
        
//         // Clear the Enter key that's still in the buffer
//         while (getchar() != '\n');
        
//         // ====================================================
//         // Now let's see what the user chose!
//         // We use if-else to make decisions
//         // ====================================================
        
//         if (user_choice == 1) {
//             // ================================================
//             // OPTION 1: Get weather for a city
//             // ================================================
            
//             printf("\n  Enter city name (for example: Dhaka, London, Tokyo): ");
            
//             // Read the city name from user
//             fgets(city_name, sizeof(city_name), stdin);
            
//             // Remove the Enter key at the end of city name
//             // We use a while loop to find it
//             int i = 0;
//             while (city_name[i] != '\0') {  // Keep going until end of text
//                 if (city_name[i] == '\n') {  // Found the Enter key!
//                     city_name[i] = '\0';      // Replace it with end marker
//                     break;                     // Stop the loop
//                 }
//                 i = i + 1;  // Move to next character
//             }
            
//             // Check if user actually typed something
//             if (strlen(city_name) == 0) {
//                 printf("\n  ERROR: You forgot to enter a city name!\n");
//             } else {
//                 // City name looks good, let's get the weather!
//                 get_weather_data(city_name);
//             }
            
//             printf("\n  Press Enter to go back to menu...");
//             getchar();
            
//         } 
//         else if (user_choice == 2) {
//             // ================================================
//             // OPTION 2: Exit the program
//             // ================================================
            
//             printf("\n  Thank you for using our Weather App!\n");
//             printf("  Have a great day!\n\n");
//             keep_running = 0;  // This will stop the while loop
            
//         } 
//         else {
//             // ================================================
//             // User entered something other than 1 or 2
//             // ================================================
            
//             printf("\n  ERROR: Please choose 1 or 2 only!\n");
//             printf("\n  Press Enter to try again...");
//             getchar();
//         }
        
//     }  // End of while loop
    
//     // Clean up and close the program
//     curl_global_cleanup();
//     return 0;
// }

// // ============================================================
// // FUNCTION: Show the program title
// // This makes our program look nice!
// // ============================================================
// void show_title(void) {
//     printf("\n");
//     printf("========================================================\n");
//     printf("             SIMPLE WEATHER APP                         \n");
//     printf("          Department of CSE - CSE 1290                 \n");
//     printf("             Get weather for any city!                  \n");
//     printf("========================================================\n");
//     printf("\n");
// }

// // ============================================================
// // FUNCTION: Show the menu options
// // ============================================================
// void show_menu(void) {
//     printf("  WHAT DO YOU WANT TO DO?\n");
//     printf("  --------------------------------------------------------\n");
//     printf("  1. Check weather for a city\n");
//     printf("  2. Exit program\n");
//     printf("  --------------------------------------------------------\n\n");
// }

// // ============================================================
// // FUNCTION: Find a number in the internet data
// // The weather data comes as text, so we need to find numbers in it
// // ============================================================
// double get_number_from_data(char *data, char *what_to_find) {
//     char search_text[100];
//     char *position;
    
//     // Make the search pattern (for example: "temp":)
//     sprintf(search_text, "\"%s\":", what_to_find);
    
//     // Try to find this pattern in our data
//     position = strstr(data, search_text);
    
//     // Did we find it?
//     if (position == NULL) {
//         return 0.0;  // Nope, return 0
//     }
    
//     // Yes! Move to where the number starts
//     position = position + strlen(search_text);
    
//     // Convert the text to a number and return it
//     return atof(position);
// }

// // ============================================================
// // FUNCTION: Find text in the internet data
// // Similar to the function above, but for text instead of numbers
// // ============================================================
// void get_text_from_data(char *data, char *what_to_find, char *where_to_save) {
//     char search_text[100];
//     char *start;
//     char *end;
//     int i;
    
//     // Make the search pattern (for example: "name":")
//     sprintf(search_text, "\"%s\":\"", what_to_find);
    
//     // Try to find this pattern
//     start = strstr(data, search_text);
    
//     // Did we find it?
//     if (start == NULL) {
//         where_to_save[0] = '\0';  // Nope, save empty text
//         return;
//     }
    
//     // Move to where the text starts
//     start = start + strlen(search_text);
//     end = start;
    
//     // Find where the text ends (at the next quote mark)
//     while (*end != '"' && *end != '\0') {
//         end = end + 1;
//     }
    
//     // Copy the text character by character
//     for (i = 0; i < (end - start) && i < 99; i++) {
//         where_to_save[i] = start[i];
//     }
//     where_to_save[i] = '\0';  // Add end marker
// }

// // ============================================================
// // FUNCTION: Get weather data from the internet
// // This is the main function that does all the work!
// // ============================================================
// void get_weather_data(char city_name[]) {
//     CURL *internet_connection;
//     CURLcode connection_result;
//     char website_address[500];
//     struct WeatherInfo weather;
    
//     printf("\n  Please wait... Getting weather data from internet...\n");
    
//     // Prepare our storage
//     data_size = 0;
//     internet_data[0] = '\0';
    
//     // Build the website address (URL) to get weather data
//     sprintf(website_address, 
//         "https://api.openweathermap.org/data/2.5/weather?q=%s&appid=%s&units=metric",
//         city_name, API_KEY);
    
//     // Start internet connection
//     internet_connection = curl_easy_init();
    
//     // Check if connection started successfully
//     if (internet_connection == NULL) {
//         printf("  ERROR: Could not connect to internet!\n");
//         return;
//     }
    
//     // Set up the connection
//     curl_easy_setopt(internet_connection, CURLOPT_URL, website_address);
//     curl_easy_setopt(internet_connection, CURLOPT_WRITEFUNCTION, save_internet_data);
//     curl_easy_setopt(internet_connection, CURLOPT_TIMEOUT, 10L);  // Wait max 10 seconds
    
//     // Try to get the data
//     connection_result = curl_easy_perform(internet_connection);
    
//     // Did we successfully get the data?
//     if (connection_result != CURLE_OK) {
//         printf("  ERROR: Could not connect to internet. Check your connection!\n");
//         curl_easy_cleanup(internet_connection);
//         return;
//     }
    
//     // Close the connection
//     curl_easy_cleanup(internet_connection);
    
//     // Check if the city was found
//     if (strstr(internet_data, "\"cod\":\"404\"") != NULL) {
//         printf("\n  ERROR: City '%s' not found!\n", city_name);
//         printf("  Please check the spelling and try again.\n");
//         return;
//     }
    
//     // Great! We got the data. Now let's extract the weather information
//     printf("  Success! Data received. Reading weather information...\n");
    
//     get_text_from_data(internet_data, "name", weather.city);
//     get_text_from_data(internet_data, "country", weather.country);
//     weather.temperature = get_number_from_data(internet_data, "temp");
//     weather.feels_like = get_number_from_data(internet_data, "feels_like");
//     weather.humidity = (int)get_number_from_data(internet_data, "humidity");
//     weather.wind_speed = get_number_from_data(internet_data, "speed");
//     get_text_from_data(internet_data, "main", weather.condition);
//     get_text_from_data(internet_data, "description", weather.description);
    
//     // Now show everything to the user
//     show_weather_report(weather);
//     show_weather_tips(weather);
// }

// // ============================================================
// // FUNCTION: Show the weather report in a nice format
// // ============================================================
// void show_weather_report(struct WeatherInfo weather) {
//     printf("\n");
//     printf("  ========================================================\n");
//     printf("  YOUR WEATHER REPORT\n");
//     printf("  ========================================================\n");
//     printf("  Location:      %s, %s\n", weather.city, weather.country);
//     printf("  --------------------------------------------------------\n");
//     printf("  Temperature:   %.1f°C\n", weather.temperature);
//     printf("  Feels Like:    %.1f°C\n", weather.feels_like);
//     printf("  Humidity:      %d%%\n", weather.humidity);
//     printf("  Wind Speed:    %.1f m/s\n", weather.wind_speed);
//     printf("  Condition:     %s\n", weather.condition);
//     printf("  Description:   %s\n", weather.description);
//     printf("  --------------------------------------------------------\n");
// }

// // ============================================================
// // FUNCTION: Show helpful tips based on the weather
// // This uses if-else to give different advice for different weather
// // ============================================================
// void show_weather_tips(struct WeatherInfo weather) {
//     printf("\n  WEATHER ADVICE: ");
    
//     // Check different weather conditions and give advice
//     // We check the most important conditions first
    
//     if (strstr(weather.condition, "Rain") != NULL) {
//         // It's raining!
//         printf("☔ It's raining! Don't forget your umbrella!\n");
//     }
//     else if (strstr(weather.condition, "Thunderstorm") != NULL) {
//         // There's a thunderstorm!
//         printf("⚡ Thunderstorm alert! Better stay indoors and safe!\n");
//     }
//     else if (strstr(weather.condition, "Snow") != NULL) {
//         // It's snowing!
//         printf("❄️ It's snowing! Wear warm clothes and be careful!\n");
//     }
//     else if (weather.temperature > 35) {
//         // Very hot weather!
//         printf("🌡️ Very hot! Drink plenty of water and stay cool!\n");
//     }
//     else if (weather.temperature < 5) {
//         // Very cold weather!
//         printf("🧊 Very cold! Wear warm clothes and stay cozy!\n");
//     }
//     else if (strstr(weather.condition, "Clear") != NULL) {
//         // Clear and sunny!
//         printf("☀️ Beautiful clear weather! Perfect day to go out!\n");
//     }
//     else if (strstr(weather.condition, "Clouds") != NULL) {
//         // Cloudy weather
//         printf("☁️ Cloudy today! Nice and cool weather!\n");
//     }
//     else {
//         // Any other weather
//         printf("🌤️ Have a wonderful day!\n");
//     }
    
//     printf("  ========================================================\n");
// }

// // ============================================================
// // END OF PROGRAM
// // ============================================================

















#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>

#define API_KEY "c8b4128ba2cb1a2c6ad45780d2fbcc6a"

struct WeatherInfo {
    char city[100];
    char country[10];
    double temperature;
    double feels_like;
    int humidity;
    double wind_speed;
    char condition[50];
    char description[100];
};

char internet_data[5000];
int data_size = 0;

void show_title(void);
void show_menu(void);
void get_weather_data(char city_name[]);
void show_weather_report(struct WeatherInfo weather);
void show_weather_tips(struct WeatherInfo weather);
double get_number_from_data(char *data, char *what_to_find);
void get_text_from_data(char *data, char *what_to_find, char *where_to_save);

// ============================================================
// TEMPERATURE CONVERSION FUNCTIONS
// Convert between Celsius, Fahrenheit, and Kelvin
// ============================================================
double celsius_to_fahrenheit(double celsius);
double celsius_to_kelvin(double celsius);

size_t save_internet_data(void *new_data, size_t size, size_t count, void *unused) {
    (void)unused;

    int total_characters = size * count;
    int i;

    for (i = 0; i < total_characters; i++) {
        if (data_size < 4999) {
            internet_data[data_size] = ((char*)new_data)[i];
            data_size = data_size + 1;
        }
    }

    internet_data[data_size] = '\0';

    return total_characters;
} // Sk Mustakin Rahman Jehan

int main(void) {
    int user_choice;
    char city_name[100];
    int keep_running = 1;

    curl_global_init(CURL_GLOBAL_DEFAULT);

    while (keep_running == 1) {

        show_title();
        show_menu();

        printf("  What would you like to do? Enter 1 or 2: ");

        if (scanf("%d", &user_choice) != 1) {
            while (getchar() != '\n');

            printf("\n  OOPS! Please enter a number (1 or 2)!\n");
            printf("\n  Press Enter to try again...");
            getchar();
            continue;
        }

        while (getchar() != '\n');

        if (user_choice == 1) {

            printf("\n  Enter city name (for example: Dhaka, London, Tokyo): ");

            fgets(city_name, sizeof(city_name), stdin);

            int i = 0;
            while (city_name[i] != '\0') {
                if (city_name[i] == '\n') {
                    city_name[i] = '\0';
                    break;
                }
                i = i + 1;
            }

            if (strlen(city_name) == 0) {
                printf("\n  ERROR: You forgot to enter a city name!\n");
            } else {
                get_weather_data(city_name);
            }

            printf("\n  Press Enter to go back to menu...");
            getchar();

        }
        else if (user_choice == 2) {

            printf("\n  Thank you for using our Weather App!\n");
            printf("  Have a great day!\n\n");
            keep_running = 0;

        }
        else {

            printf("\n  ERROR: Please choose 1 or 2 only!\n");
            printf("\n  Press Enter to try again...");
            getchar();
        }

    }

    curl_global_cleanup();
    return 0;
}// Sk Mustakin Rahman Jehan

void show_title(void) {
    printf("\n");
    printf("========================================================\n");
    printf("             SIMPLE WEATHER APP                         \n");
    printf("          Department of CSE - CSE 1290                 \n");
    printf("             Get weather for any city!                  \n");
    printf("========================================================\n");
    printf("\n");
}

void show_menu(void) {
    printf("  WHAT DO YOU WANT TO DO?\n");
    printf("  --------------------------------------------------------\n");
    printf("  1. Check weather for a city\n");
    printf("  2. Exit program\n");
    printf("  --------------------------------------------------------\n\n");
} // Sk Mustakin Rahman Jehan

double get_number_from_data(char *data, char *what_to_find) {
    char search_text[100];
    char *position;

    sprintf(search_text, "\"%s\":", what_to_find);

    position = strstr(data, search_text);

    if (position == NULL) {
        return 0.0;
    }

    position = position + strlen(search_text);

    return atof(position);
}// Md Anik reza

void get_text_from_data(char *data, char *what_to_find, char *where_to_save) {
    char search_text[100];
    char *start;
    char *end;
    int i;

    sprintf(search_text, "\"%s\":\"", what_to_find);

    start = strstr(data, search_text);

    if (start == NULL) {
        where_to_save[0] = '\0';
        return;
    }

    start = start + strlen(search_text);
    end = start;

    while (*end != '"' && *end != '\0') {
        end = end + 1;
    }

    for (i = 0; i < (end - start) && i < 99; i++) {
        where_to_save[i] = start[i];
    }
    where_to_save[i] = '\0';
}// Md Aink Reza

void get_weather_data(char city_name[]) {
    CURL *internet_connection;
    CURLcode connection_result;
    char website_address[500];
    struct WeatherInfo weather;

    printf("\n  Please wait... Getting weather data from internet...\n");

    data_size = 0;
    internet_data[0] = '\0';

    sprintf(website_address,
        "https://api.openweathermap.org/data/2.5/weather?q=%s&appid=%s&units=metric",
        city_name, API_KEY);

    internet_connection = curl_easy_init();

    if (internet_connection == NULL) {
        printf("  ERROR: Could not connect to internet!\n");
        return;
    }

    curl_easy_setopt(internet_connection, CURLOPT_URL, website_address);
    curl_easy_setopt(internet_connection, CURLOPT_WRITEFUNCTION, save_internet_data);
    curl_easy_setopt(internet_connection, CURLOPT_TIMEOUT, 10L);

    connection_result = curl_easy_perform(internet_connection);

    if (connection_result != CURLE_OK) {
        printf("  ERROR: Could not connect to internet. Check your connection!\n");
        curl_easy_cleanup(internet_connection);
        return;
    }

    curl_easy_cleanup(internet_connection);

    if (strstr(internet_data, "\"cod\":\"404\"") != NULL) {
        printf("\n  ERROR: City '%s' not found!\n", city_name);
        printf("  Please check the spelling and try again.\n");
        return;
    }

    printf("  Success! Data received. Reading weather information...\n");

    get_text_from_data(internet_data, "name", weather.city);
    get_text_from_data(internet_data, "country", weather.country);
    weather.temperature = get_number_from_data(internet_data, "temp");
    weather.feels_like = get_number_from_data(internet_data, "feels_like");
    weather.humidity = (int)get_number_from_data(internet_data, "humidity");
    weather.wind_speed = get_number_from_data(internet_data, "speed");
    get_text_from_data(internet_data, "main", weather.condition);
    get_text_from_data(internet_data, "description", weather.description);

    show_weather_report(weather);
    show_weather_tips(weather);
}// Sk Mustakin Rahman Jehan

// ============================================================
// FUNCTION: Convert Celsius to Fahrenheit
// Formula: F = (C × 9/5) + 32
// ============================================================
double celsius_to_fahrenheit(double celsius) {
    return (celsius * 9.0 / 5.0) + 32.0;
}

// ============================================================
// FUNCTION: Convert Celsius to Kelvin
// Formula: K = C + 273.15
// ============================================================
double celsius_to_kelvin(double celsius) {
    return celsius + 273.15;
}

void show_weather_report(struct WeatherInfo weather) {
    // Calculate temperature in all units
    double temp_fahrenheit = celsius_to_fahrenheit(weather.temperature);
    double temp_kelvin = celsius_to_kelvin(weather.temperature);
    double feels_fahrenheit = celsius_to_fahrenheit(weather.feels_like);
    double feels_kelvin = celsius_to_kelvin(weather.feels_like);

    printf("\n");
    printf("  ========================================================\n");
    printf("  YOUR WEATHER REPORT\n");
    printf("  ========================================================\n");
    printf("  Location:      %s, %s\n", weather.city, weather.country);
    printf("  --------------------------------------------------------\n");
    printf("\n");
    printf("  TEMPERATURE (in different units):\n");
    printf("    Celsius:     %.1f°C\n", weather.temperature);
    printf("    Fahrenheit:  %.1f°F\n", temp_fahrenheit);
    printf("    Kelvin:      %.1f K\n", temp_kelvin);
    printf("\n");
    printf("  FEELS LIKE (in different units):\n");
    printf("    Celsius:     %.1f°C\n", weather.feels_like);
    printf("    Fahrenheit:  %.1f°F\n", feels_fahrenheit);
    printf("    Kelvin:      %.1f K\n", feels_kelvin);
    printf("\n");
    printf("  --------------------------------------------------------\n");
    printf("  Humidity:      %d%%\n", weather.humidity);
    printf("  Wind Speed:    %.1f m/s\n", weather.wind_speed);
    printf("  Condition:     %s\n", weather.condition);
    printf("  Description:   %s\n", weather.description);
    printf("  --------------------------------------------------------\n");
} //Sadia Tabassum Neha

void show_weather_tips(struct WeatherInfo weather) {
    printf("\n  WEATHER ADVICE: ");

    if (strstr(weather.condition, "Rain") != NULL) {
        printf("☔ It's raining! Don't forget your umbrella!\n");
    }
    else if (strstr(weather.condition, "Thunderstorm") != NULL) {
        printf("⚡ Thunderstorm alert! Better stay indoors and safe!\n");
    }
    else if (strstr(weather.condition, "Snow") != NULL) {
        printf("❄️ It's snowing! Wear warm clothes and be careful!\n");
    }
    else if (weather.temperature > 35) {
        printf("🌡️ Very hot! Drink plenty of water and stay cool!\n");
    }
    else if (weather.temperature < 5) {
        printf("🧊 Very cold! Wear warm clothes and stay cozy!\n");
    }
    else if (strstr(weather.condition, "Clear") != NULL) {
        printf("☀️ Beautiful clear weather! Perfect day to go out!\n");
    }
    else if (strstr(weather.condition, "Clouds") != NULL) {
        printf("☁️ Cloudy today! Nice and cool weather!\n");
    }
    else {
        printf("🌤️ Have a wonderful day!\n");
    }

    printf("  ========================================================\n");
}//Sadia Tabassum Neha