#include "../lib/frequency.h"
#include "../lib/base64.c"

int main () {

    char *B64Text = "HUIfTQsPAh9PE048GmllH0kcDk4TAQsHThsBFkU2AB4BSWQgVB0dQzNTTmVSBgBHVBwNRU0HBAxTEjwMHghJGgkRTxRMIRpHKwAFHUdZEQQJAGQmB1MANxYGDBoXQR0BUlQwXwAgEwoFR0$";
    char *buf = malloc(Base64decode_len(B64Text));

    Base64decode(buf, B64Text);
    RepeatedXorAnalysis(buf, Base64decode_len(B64Text) - 1);
}
