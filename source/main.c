#include <gccore.h>
#include <network.h>
#include <stdio.h>
#include <wiiuse/wpad.h>

#include "nand.h"
#include "network.h"
#include "patcher.h"

#define textPos(x, y) printf("\x1b[%d;%dH", y, x)
#define htons(x) (x)

static void* xfb = NULL;
static GXRModeObj* rmode = NULL;

int main(void) {

    VIDEO_Init();
    WPAD_Init();
    initNetwork();
    NAND_Init();

    rmode = VIDEO_GetPreferredMode(NULL);
    xfb = MEM_K0_TO_K1(SYS_AllocateFramebuffer(rmode));
    console_init(xfb, 20, 20, rmode->fbWidth, rmode->xfbHeight, rmode->fbWidth * VI_DISPLAY_PIX_SZ);
    VIDEO_Configure(rmode);
    VIDEO_SetNextFramebuffer(xfb);
    VIDEO_SetBlack(FALSE);
    VIDEO_Flush();
    VIDEO_WaitVSync();
    if (rmode->viTVMode & VI_NON_INTERLACE) VIDEO_WaitVSync();

    printf("\n\nRunning...\n\n\n\n\n");
    s32 systemVersion = getSystemMenuVersion();

    if (systemVersion < 256) printf("Your System Menu is outdated.\nPlease update to the latest version of the Wii system.");
    else {
        if (systemVersion >= 256 && systemVersion < 512) 
            printf("Disconnect24 works best on 4.3. If you update, You will need to repatch.\nHowever, the Installer will continue.\n");

        s32 error = patchMail();
        if (error == RESPONSE_AREGISTERED) printf("If your previous registration failed, please\ncontact a developer at support@disconnect24.xyz.\n");
        else if (error != 0) printf("An error occurred! Please send a screenshot of this error message\nto a developer or at support@disconnect24.net.\n");
        else printf("Finished!\nPress HOME to exit.\n");
    }

    while (1) {
        WPAD_ScanPads();
        u32 pressed = WPAD_ButtonsDown(0);
        if (pressed & WPAD_BUTTON_HOME) exit(0);
        VIDEO_WaitVSync();
    }

    NAND_Exit();
    return 0;
}
