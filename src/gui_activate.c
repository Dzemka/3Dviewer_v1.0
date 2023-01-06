#include "viewer3D.h"

void gui_activate(t_viewer *viewer, GtkWidget *win) {
    GtkWidget *box_main;
    GtkWidget *box_buttons_left;
    GtkWidget *box_model;
    GtkWidget *box_buttons_right;

    box_main = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
//    gtk_box_set_homogeneous(GTK_BOX(box_main), FALSE);
    box_buttons_left = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_widget_set_size_request(box_buttons_left, 280, 100);
    box_model = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);

//    gtk_widget_set_size_request(box_model, 640, 480);

    box_buttons_right = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_widget_set_size_request(box_buttons_right, 280, 100);

    viewer->model = gtk_drawing_area_new();
    gtk_window_set_child(GTK_WINDOW(win), box_main);
    gtk_box_append(GTK_BOX(box_main), box_buttons_left);
    gtk_box_append(GTK_BOX(box_main), box_model);
    gtk_box_append(GTK_BOX(box_model), viewer->model);
    gtk_box_append(GTK_BOX(box_main), box_buttons_right);
    buttons_manager(viewer, box_buttons_left, box_buttons_right);

    draw_model(viewer);
}