#include <stdio.h>
#include <conio.h>

int main() {
    char key;

    printf("Press 1 (ON), 2 (OFF), or 3 (Exit)\n");

    while (1) {
        key = _getch();

        if (key == '1') {
            printf("Publishing ON...\n");
            // Replace the IP address if restarting gcp until DNS is set up
            system("mosquitto_pub -h 35.197.26.221 -p 1883 -t esp32/led -m ON");
        }
        else if (key == '2') {
            printf("Publishing OFF...\n");
            system("mosquitto_pub -h 35.197.26.221 -p 1883 -t esp32/led -m OFF");
        }
        else if (key == '3') {
            printf("Exiting program.\n");
            break;
        }
        else {
            printf("Invalid key: press 1 (ON), 2 (OFF), or 3 (Exit)\n");
        }
    }

    return 0;
}
