#include "viewer3D.h"

static void draw(t_viewer *viewer, cairo_t *cr) {
    int i;
    t_list *list;
    t_plane *plane;
    double coord_x;
    double coord_y;
    size_t index_vertex;

    list = viewer->info.faces;
    draw_settings(viewer, cr);
    while (list) {
        plane = (t_plane *) list->content;
        i = -1;
        while (++i < (int) plane->size) {
            index_vertex = (plane->indexes[i % plane->size] -
                            1);
            coord_x = viewer->info.vertexes2d[index_vertex * 2];
            coord_y = viewer->info.vertexes2d[index_vertex * 2 + 1];
            cairo_move_to(cr, coord_x, coord_y);
            index_vertex = (plane->indexes[(i + 1) % plane->size] - 1);
            coord_x = viewer->info.vertexes2d[index_vertex * 2];
            coord_y = viewer->info.vertexes2d[index_vertex * 2 + 1];
            cairo_line_to(cr, coord_x, coord_y);
        }
        cairo_stroke(cr);
        list = list->next;
    }
    cairo_stroke(cr);
}

static void clear_surface(cairo_surface_t *surface)//////////новое
{
    cairo_t *cr;

    cr = cairo_create(surface);

    cairo_set_source_rgb(cr, 0, 0, 0);
    cairo_paint(cr);

    cairo_destroy(cr);
}

static void draw_function(GtkDrawingArea *area, cairo_t *cr, int width,
                          int height, gpointer pointer) {
    t_viewer *viewer;
    cairo_t *cr1;

    viewer = pointer;
    cairo_surface_t *surface = NULL;
    if (surface) {
        cairo_surface_destroy(surface);
        surface = NULL;
    }
    if (gtk_native_get_surface(gtk_widget_get_native(viewer->model))) {
        surface = gdk_surface_create_similar_surface(gtk_native_get_surface(gtk_widget_get_native(viewer->model)),
                                                     CAIRO_CONTENT_COLOR,
                                                     gtk_widget_get_width(viewer->model),
                                                     gtk_widget_get_height(viewer->model));
    }
    cr1 = cairo_create(surface);
    viewer->func_proj(viewer, width, height);
    cairo_set_source_rgb(cr1, viewer->info.background_color.red, viewer->info.background_color.green,
                         viewer->info.background_color.blue);
    cairo_rectangle(cr1, 0, 0, width, height);
    cairo_fill(cr1);
    draw(viewer, cr1);
    cairo_destroy(cr1);
    cairo_paint(cr1);
    cairo_set_source_surface(cr, surface, 0, 0);///////////////новое
    cairo_paint(cr);
    if (viewer->info.make_screenshot)
        get_screenshot(viewer, surface);
}

static void
resize_cb(GtkWidget *widget,
          int width,
          int height,
          gpointer data) {
    printf("%d %d\n", width, height);
}

void draw_model(t_viewer *viewer) {
    gtk_widget_set_size_request(viewer->model, 640, 480);
    gtk_drawing_area_set_draw_func(GTK_DRAWING_AREA(viewer->model), draw_function,
                                   viewer, NULL);
}