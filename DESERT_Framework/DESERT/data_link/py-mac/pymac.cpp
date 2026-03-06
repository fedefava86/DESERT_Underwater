// Python headers should be the very first thing we pull in.  Some
// third-party headers (mmac, Tcl, etc.) may themselves include Python.h with
// limited-API macros or undefine symbols later, so we protect ourselves by
// defining the missing bits both before and after including them.
#include <Python.h>
#ifndef Py_REFCNT
// direct field access if the standard macro is absent
#    define Py_REFCNT(ob) (((PyObject*)(ob))->ob_refcnt)
#endif
#ifndef _Py_REFCNT
#    define _Py_REFCNT(ob) (((PyObject*)(ob))->ob_refcnt)
#endif
// ensure rich-compare is declared even if Python.h was brought in with
// Py_LIMITED_API or otherwise skipped it
#ifndef PyObject_RichCompareBool
extern "C" int PyObject_RichCompareBool(PyObject *a, PyObject *b, int op);
#endif

#include "pymac.h"

// some headers included by pymac.h (e.g. mmac.h) may undefine the macros above
// or re-include Python.h; redefine them again so pybind11 sees them.
#ifndef Py_REFCNT
#    define Py_REFCNT(ob) (((PyObject*)(ob))->ob_refcnt)
#endif
#ifndef _Py_REFCNT
#    define _Py_REFCNT(ob) (((PyObject*)(ob))->ob_refcnt)
#endif
#ifndef PyObject_RichCompareBool
extern "C" int PyObject_RichCompareBool(PyObject *a, PyObject *b, int op);
#endif

#include <tclcl.h>
#include <pybind11/embed.h> // Everything needed for embedding
namespace py = pybind11;

// Tcl registration so ns-2 can create the object from OTcl scripts.
static class PyMacClass : public TclClass {
public:
    PyMacClass() : TclClass("Module/UW/DataLink/PyMac") {}
    TclObject* create(int, const char*const*) override {
        return (new PyMac());
    }
} class_pymac;

PyMac::PyMac() : MMac()
{
    // nothing to initialize
	static py::scoped_interpreter guard{};
}

PyMac::~PyMac()
{
    // no dynamic resources
}

int PyMac::command(int argc, const char*const* argv)
{
    // forward unknown commands to the base class
    return MMac::command(argc, argv);
}

void PyMac::recv(Packet* p)
{
    // drop every packet that arrives, marking it with a generic reason
	py::module_ calc = py::module_::import("mac_logic");
    drop(p, 1, 0); // 1=receive drop, reason 0=unspecified
}