#include "map.h"

#include "editor/editor.h"
#include "game/game.h"
#include "graphics/generic_button.h"
#include "graphics/graphics.h"
#include "graphics/image.h"
#include "graphics/lang_text.h"
#include "graphics/panel.h"
#include "graphics/window.h"
#include "window/popup_dialog.h"

static void button_click(int type, int param2);

static int focus_button_id;

static generic_button buttons[] = {
    {192, 100, 448, 125, GB_IMMEDIATE, button_click, button_none, 1, 0},
};

static void draw_background(void)
{
    graphics_clear_screen();
    image_draw_fullscreen_background(image_group(GROUP_ADVISOR_BACKGROUND));
}

static void draw_foreground(void)
{
    graphics_in_dialog();

    large_label_draw(192, 100, 16, focus_button_id == 1 ? 1 : 0);

    lang_text_draw_centered(7, 4, 192, 106, 256, FONT_NORMAL_GREEN);

    graphics_reset_dialog();
}

static void handle_mouse(const mouse *m)
{
    generic_buttons_handle_mouse(mouse_in_dialog(m), 0, 0, buttons, 1, &focus_button_id);
}

static void confirm_exit(int accepted)
{
    if (accepted) {
        game_exit_editor();
    }
}

static void button_click(int type, int param2)
{
    window_popup_dialog_show(POPUP_DIALOG_QUIT, confirm_exit, 1);
}

void window_editor_map_show(void)
{
    window_type window = {
        WINDOW_EDITOR_MAP,
        draw_background,
        draw_foreground,
        handle_mouse
    };
    window_show(&window);
}
