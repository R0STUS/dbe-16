#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <locale>
#include <gtk/gtk.h>
#include <codecvt>
#include "dbe16.hpp"

GtkWidget *text_view;

void open_file(GtkWidget *widget, gpointer window) {
    GtkWidget *dialog;
    dialog = gtk_file_chooser_dialog_new("Open File", GTK_WINDOW(window), GTK_FILE_CHOOSER_ACTION_OPEN, "Cancel", GTK_RESPONSE_CANCEL, "Open", GTK_RESPONSE_ACCEPT, NULL);
    if (gtk_dialog_run(GTK_DIALOG(dialog)) == GTK_RESPONSE_ACCEPT) {
        char *filename;
        GtkTextBuffer *buffer;
        filename = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(dialog));

        std::string hexString = DBE16::readfile(filename); // Reading and converting binary values from file

        if (!hexString.empty()) {
            buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(text_view));
            gtk_text_buffer_set_text(buffer, hexString.c_str(), -1);
        }
        g_free(filename);
    }
    gtk_widget_destroy(dialog);
}

void save_file(GtkWidget *widget, gpointer window) {
    GtkWidget *dialog;
    dialog = gtk_file_chooser_dialog_new("Save File", GTK_WINDOW(window), GTK_FILE_CHOOSER_ACTION_SAVE, "Cancel", GTK_RESPONSE_CANCEL, "Save", GTK_RESPONSE_ACCEPT, NULL);
    if (gtk_dialog_run(GTK_DIALOG(dialog)) == GTK_RESPONSE_ACCEPT) {
        char *filename;
        GtkTextBuffer *buffer;
        filename = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(dialog));
        buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(text_view));
        GtkTextIter start, end;
        gtk_text_buffer_get_bounds(buffer, &start, &end);
        gchar *text = gtk_text_buffer_get_text(buffer, &start, &end, FALSE);
        std::string inputText(text);

        std::string hexValues = DBE16::converttohex(inputText); // Converting text to DBE-16 Encoding

        DBE16::writefile(filename, hexValues); // Saving binary values to file

        g_free(text);
        g_free(filename);
    }
    gtk_widget_destroy(dialog);
}

int main(int argc, char *argv[]) {
    gtk_init(&argc, &argv);
    GtkWidget *window;
    GtkWidget *vbox;
    GtkWidget *menubar;
    GtkWidget *file_menu;
    GtkWidget *file_item;
    GtkWidget *open_item;
    GtkWidget *save_item;
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "DBE-16 Editor");
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
    vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_container_add(GTK_CONTAINER(window), vbox);
    menubar = gtk_menu_bar_new();
    file_menu = gtk_menu_new();
    file_item = gtk_menu_item_new_with_label("File");
    open_item = gtk_menu_item_new_with_label("Open");
    save_item = gtk_menu_item_new_with_label("Save");
    g_signal_connect(open_item, "activate", G_CALLBACK(open_file), window);
    g_signal_connect(save_item, "activate", G_CALLBACK(save_file), window);
    gtk_menu_shell_append(GTK_MENU_SHELL(file_menu), open_item);
    gtk_menu_shell_append(GTK_MENU_SHELL(file_menu), save_item);
    gtk_menu_item_set_submenu(GTK_MENU_ITEM(file_item), file_menu);
    gtk_menu_shell_append(GTK_MENU_SHELL(menubar), file_item);
    gtk_box_pack_start(GTK_BOX(vbox), menubar, FALSE, FALSE, 0);
    text_view = gtk_text_view_new();
    gtk_box_pack_start(GTK_BOX(vbox), text_view, TRUE, TRUE, 0);
    gtk_widget_show_all(window);
    gtk_main();
    return 0;
}