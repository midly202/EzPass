#include <string>

const std::string FILE_NAME = "logins.dat";
const char XOR_KEY = 0x5A;

const std::string letters = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
const std::string numbers = "0123456789";
const std::string specialCharacters = "!@#$%^&*()-_=+[]{}|;:,.<>?";
const std::string lettersAndNumbersAndSpecial = letters + numbers + specialCharacters;

// Standard colors
const std::string RESET = "\033[0m";
const std::string BLACK = "\033[30m";
const std::string RED = "\033[31m";
const std::string GREEN = "\033[32m";
const std::string YELLOW = "\033[33m";
const std::string BLUE = "\033[34m";
const std::string MAGENTA = "\033[35m";
const std::string CYAN = "\033[36m";
const std::string WHITE = "\033[37m";

// Bright colors
const std::string BRIGHT_BLACK = "\033[90m";
const std::string BRIGHT_RED = "\033[91m";
const std::string BRIGHT_GREEN = "\033[92m";
const std::string BRIGHT_YELLOW = "\033[93m";
const std::string BRIGHT_BLUE = "\033[94m";
const std::string BRIGHT_MAGENTA = "\033[95m";
const std::string BRIGHT_CYAN = "\033[96m";
const std::string BRIGHT_WHITE = "\033[97m";

// Backgrounds (standard)
const std::string BG_BLACK = "\033[40m";
const std::string BG_RED = "\033[41m";
const std::string BG_GREEN = "\033[42m";
const std::string BG_YELLOW = "\033[43m";
const std::string BG_BLUE = "\033[44m";
const std::string BG_MAGENTA = "\033[45m";
const std::string BG_CYAN = "\033[46m";
const std::string BG_WHITE = "\033[47m";

// Backgrounds (bright)
const std::string BG_BRIGHT_BLACK = "\033[100m";
const std::string BG_BRIGHT_RED = "\033[101m";
const std::string BG_BRIGHT_GREEN = "\033[102m";
const std::string BG_BRIGHT_YELLOW = "\033[103m";
const std::string BG_BRIGHT_BLUE = "\033[104m";
const std::string BG_BRIGHT_MAGENTA = "\033[105m";
const std::string BG_BRIGHT_CYAN = "\033[106m";
const std::string BG_BRIGHT_WHITE = "\033[107m";

// Text effects
const std::string BOLD = "\033[1m";
const std::string UNDERLINE = "\033[4m";
const std::string BLINK = "\033[5m";
const std::string INVERT = "\033[7m";
const std::string HIDDEN = "\033[8m";

// 256-color mode (text)
const std::string ORANGE_256 = "\033[38;5;208m";
const std::string PINK_256 = "\033[38;5;200m";
const std::string TEAL_256 = "\033[38;5;37m";
const std::string GREY_256 = "\033[38;5;244m";
const std::string PURPLE_256 = "\033[38;5;129m";
const std::string NEON_GREEN_256 = "\033[38;5;118m";
const std::string SKY_BLUE_256 = "\033[38;5;75m";

// RGB True Color (foreground)
const std::string RGB_PURPLE = "\033[38;2;204;153;255m";
const std::string RGB_PINK = "\033[38;2;255;105;180m";
const std::string RGB_ORANGE = "\033[38;2;255;165;0m";
const std::string RGB_SKY = "\033[38;2;135;206;250m";
const std::string RGB_AQUA = "\033[38;2;0;255;255m";
const std::string RGB_LIME = "\033[38;2;50;205;50m";
const std::string RGB_GOLD = "\033[38;2;255;215;0m";
const std::string RGB_CORAL = "\033[38;2;255;127;80m";
const std::string RGB_INDIGO = "\033[38;2;75;0;130m";
const std::string RGB_MINT = "\033[38;2;152;255;152m";

struct Login
{
    std::string name;
    std::string email;
    std::string user;
    std::string pass;
    int length;
};
