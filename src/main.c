/* vim:set et sts=4: */

#include <ibus.h>
#include "engine.h"

static IBusBus *bus = NULL;
static IBusFactory *factory = NULL;

static void
ibus_disconnected_cb (IBusBus  *bus,
                      gpointer  user_data)
{
    ibus_quit ();
}

static void
init (void)
{
    ibus_init ();
    
    bus = ibus_bus_new ();
    g_signal_connect (bus, "disconnected", G_CALLBACK (ibus_disconnected_cb), NULL);
	
    factory = ibus_factory_new ("/org/freedesktop/IBus/enchant/Factory",
								ibus_bus_get_connection (bus),
								"English Writer",
								"en",
								PKGDATADIR "/icons/ibus-enchant.svg",
								"Peng Huang <shawn.p.huang@gmail.com>",
								"GPLv2",
								"/org/freedesktop/IBus/enchant/Engine",
								IBUS_TYPE_ENCHANT_ENGINE);
}

int main()
{

    init ();
    ibus_bus_register_factory (bus, factory);
    ibus_main ();
}