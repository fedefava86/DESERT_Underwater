#ifndef PYMAC_H
#define PYMAC_H

#include <mmac.h>

/**
 * @brief A minimal MAC protocol that does nothing.
 *
 * This class exists only to provide the bare minimum implementation of an
 * MMac-derived module so that it can be compiled and instantiated by the
 * simulator.  All packets received are dropped and no timers or state are
 * managed.
 */
class PyMac : public MMac
{
public:
    PyMac();
    virtual ~PyMac();

    /**
     * Tcl command interpreter.  Delegates to the base class implementation.
     */
    virtual int command(int argc, const char*const* argv) override;

    /**
     * Called when a packet arrives from the lower layer (phy).  This
     * implementation simply drops every packet.
     */
    virtual void recv(Packet* p) override;
};

#endif // PYMAC_H