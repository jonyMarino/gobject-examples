#include <stdio.h>
#include <glib-object.h>
#include <glib.h>
#include <gobject/gtype.h>
#include "base.h"
#include "derived.h"

void my_dump_type(GType type_id) {
    g_print("Type id: %d\n", type_id);
    g_print("Type name: %s\n", g_type_name(type_id));
    g_print("Is fundamental? %s\n", G_TYPE_IS_FUNDAMENTAL(type_id) ? "yes" : "no");
    g_print("Is derived? %s\n", G_TYPE_IS_DERIVED(type_id) ? "yes" : "no");
    g_print("Is interface? %s\n", G_TYPE_IS_INTERFACE(type_id) ? "yes" : "no");
    g_print("Is classed? %s\n", G_TYPE_IS_CLASSED(type_id) ? "yes" : "no");
    g_print("Is instantiatable? %s\n", G_TYPE_IS_INSTANTIATABLE(type_id) ? "yes" : "no");
    g_print("Is derivable? %s\n", G_TYPE_IS_DERIVABLE(type_id) ? "yes" : "no");
    g_print("Is deep derivable? %s\n", G_TYPE_IS_DEEP_DERIVABLE(type_id) ? "yes" : "no");
    g_print("Is abstract? %s\n", G_TYPE_IS_ABSTRACT(type_id) ? "yes" : "no");
    g_print("Is value abstract? %s\n", G_TYPE_IS_VALUE_ABSTRACT(type_id) ? "yes" : "no");
    g_print("Is value type: %s\n", G_TYPE_IS_VALUE_TYPE(type_id) ? "yes" : "no");
    g_print("Has value table: %s\n", G_TYPE_HAS_VALUE_TABLE(type_id) ? "yes" : "no");
}

int main(int argc, char ** argv){
//#if 0
	GTypeClass a;
	GList* list = NULL;
    list = g_list_append(list, "Hello world!");
    char* str = g_list_first(list)->data;
    printf("The first item is '%s'\n", str);
//#endif

    my_dump_type(base_get_type());
    my_dump_type(derived_get_type());

    /*
     * Official document:
     * Use of g_type_create_instance() is reserved for implementators of
     * fundamental types only. E.g. instances of the GObject hierarchy should
     * be created via g_object_new() and never directly through
     * g_type_create_instance() which doesn't handle things like singleton
     * objects or object construction.
     */
    Base *base = (Base *)g_type_create_instance(base_get_type());
    base_class_set_i(101);
    base_instance_set_i(base, 201);
    Derived *derived = (Derived *)g_type_create_instance(derived_get_type());
    derived_instance_set_i(derived, 401);

    /* Test polymorphism */
    Base *instances[2] = { base, (Base *)derived };
    int i;
    for (i = 0; i < 2; i++) {
        Base *inst = instances[i];
        BaseClass *klass = G_TYPE_INSTANCE_GET_CLASS(inst, base_get_type(), BaseClass);
        klass->base_instance_dump(inst);
    }

    return 0;

}
