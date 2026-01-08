# Weather Forecasting System

A lightweight terminal-based weather application written in C that fetches real-time weather data from OpenWeatherMap API.

## Features

✅ **Real-time Weather Data** - Fetches current weather conditions from OpenWeatherMap API  
✅ **Clean CLI Interface** - User-friendly terminal menu system  
✅ **Smart Caching** - Reduces API calls by caching data for 30 minutes  
✅ **Comprehensive Information** - Temperature, feels-like, humidity, wind speed, conditions  
✅ **Weather Alerts** - Contextual messages based on weather conditions  
✅ **Error Handling** - Handles network failures, invalid cities, and API errors  
✅ **Fast & Lightweight** - Minimal memory usage and quick performance  

## Requirements

- **GCC** compiler
- **libcurl** development library
- **OpenWeatherMap API key** (free tier available)

### Installing libcurl

**macOS:**
```bash
brew install curl
```

**Ubuntu/Debian:**
```bash
sudo apt-get install libcurl4-openssl-dev
```

**Fedora/RHEL:**
```bash
sudo dnf install libcurl-devel
```

## Setup

### 1. Get API Key

1. Visit [OpenWeatherMap](https://openweathermap.org/api)
2. Sign up for a free account
3. Generate an API key from your account dashboard

### 2. Configure API Key

Open `weather_system.c` and replace the placeholder with your API key:

```c
#define API_KEY "YOUR_API_KEY_HERE"  // Replace with your actual API key
```

### 3. Compile

```bash
make
```

Or compile manually:

```bash
gcc -Wall -Wextra -O2 -o weather_system weather_system.c -lcurl
```

## Usage

Run the program:

```bash
./weather_system
```

### Menu Options

1. **Get Current Weather** - Enter a city name to fetch weather data
2. **Exit** - Close the application

### Example Session

```
╔═══════════════════════════════════════════════════════════╗
║                                                           ║
║          🌤️  WEATHER FORECASTING SYSTEM 🌤️               ║
║                                                           ║
║              Department of CSE - CSE 1290                ║
║                                                           ║
╚═══════════════════════════════════════════════════════════╝

  📋 Menu:
  ───────────────────────────────────────────────────────
  1. Get Current Weather
  2. Exit
  ───────────────────────────────────────────────────────

  Enter your choice: 1

  🌍 Enter city name: London

  🔍 Checking cache...
  📡 Fetching live weather data...
  ───────────────────────────────────────────────────────

  📍 Location: London, GB

  ───────────────────────────────────────────────────────

  🌡️  Temperature:     15.3°C
  🤔 Feels Like:      13.8°C
  💧 Humidity:        72%
  💨 Wind Speed:      4.5 m/s
  ☁️  Condition:       Clouds
  📝 Description:     scattered clouds

  ───────────────────────────────────────────────────────

  💡 Weather Alert:
  ☁️  Cloudy – Comfortable weather!

  ───────────────────────────────────────────────────────
```

## Features Explained

### Caching System

The application automatically caches weather data for 30 minutes to:
- Reduce API calls (free tier has limits)
- Improve response time
- Work better on slow internet

Cache file: `.weather_cache.txt` (created automatically)

### Weather Alerts

The system provides contextual alerts based on conditions:

- ☔ Rain warnings
- ⚡ Thunderstorm alerts
- ❄️ Snow advisories
- 🌡️ Heat warnings (>35°C)
- 🥶 Cold warnings (<5°C)
- ☀️ Clear sky notifications

### Error Handling

- **Invalid city names** - Shows helpful error message
- **Network failures** - Detects connection issues
- **API errors** - Handles API rate limits and errors
- **Invalid input** - Validates user input

## Makefile Commands

```bash
make           # Build the program
make clean     # Remove build artifacts and cache
make install   # Install to /usr/local/bin (requires sudo)
make uninstall # Remove from /usr/local/bin (requires sudo)
make help      # Show available commands
```

## Troubleshooting

### "City not found" error
- Check spelling of city name
- Try adding country code: "London,UK"
- Use major city names

### Compilation errors
- Ensure libcurl is installed: `curl-config --version`
- Check GCC is installed: `gcc --version`

### API errors
- Verify API key is correct
- Check internet connection
- Ensure you haven't exceeded free tier limits (60 calls/minute)

### Cache issues
- Delete cache file: `rm .weather_cache.txt`
- Cache expires after 30 minutes automatically

## Project Information

**Course:** Software Development – I (CSE 1290)  
**Department:** CSE  
**Topic:** Weather Forecasting System  

**Group 09:**
- SK Mustakin Rahman Jehan (42250202831)
- Md. Anik Reza (42250202681)
- Sadiya (42250202831)

**Instructor:** Aparna Das (Lecturer)

## License

This is an educational project created for academic purposes.

## API Attribution

Weather data provided by [OpenWeatherMap](https://openweathermap.org/)
# weather-app-cpp
