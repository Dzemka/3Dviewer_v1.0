#include "../viewer3D.h"

static void rotate_pos(GtkButton *btn, t_viewer *viewer)
{

    double rotate_value;

    rotate_value = 0;
    rotate_value = atof(gtk_entry_buffer_get_text(gtk_entry_get_buffer(GTK_ENTRY(viewer->entry.entry_rotate_x)))) * M_PI / 180;
    rotate(viewer, 0, rotate_value);
}

void input_rotating_x(t_viewer *viewer, GtkWidget *box_rotating) {
    GtkWidget *box_x;
    GtkWidget *button;

    box_x = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    gtk_box_append(GTK_BOX(box_rotating), box_x);
    viewer->entry.entry_rotate_x = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(viewer->entry.entry_rotate_x), "input radian for rotate x");
    button = gtk_button_new_with_label("Rotate x");
    gtk_box_append(GTK_BOX(box_x), viewer->entry.entry_rotate_x);
    gtk_box_append(GTK_BOX(box_x), button);
    g_signal_connect(GTK_BUTTON(button), "clicked", G_CALLBACK(rotate_pos), viewer);
}