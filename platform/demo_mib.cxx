#include "vtss_appl_serialize.hxx"
#include "demo_serializer.hxx"

#include "demo_api.h"

#ifdef VTSS_SW_OPTION_WEB
#include "web_api.h"
#endif


using namespace vtss;
using namespace vtss::expose::snmp;
using namespace vtss::demo;


// (1) --- Top definition for the MIB.
//         The 1st argument "DemoMib" means that the MODULE-IDENTITY will be 'vtssDemoMib'.
//         The vtssDemoMib will be located under { vtssSwitchMgmt <VTSS_MODULE_ID_DEMO_SNMP> }
//         where <VTSS_MODULE_ID_DEMO_SNMP> is the value of VTSS_MODULE_ID_DEMO_SNMP which must be
//         defined in vtss_appl/include/vtss/appl/module_id.h.
//
//         The demo_mib_init() is function that will be generated, and which must be
//         called at system startup. See in demo.cxx.
//
//         If you build this example as described in the doc/README file, and load the result
//         onto a target and run http://<TARGET-IP-ADDRESS>/VTSS-DEMO-MIB.mib, you can
//         compare how identifiered in the MIB file is constructed from the code.
//
//         The VTSS-DEMO-MIB.mib file is provided in the doc folder if you want to look it
//         trying to build the code.
//
VTSS_MIB_MODULE("DemoMib", "DEMO", demo_mib_init, VTSS_MODULE_ID_DEMO_SNMP, demo_root, h)
{
  h.add_history_element("201901010000Z", "Initial version");
  h.add_history_element("201901010001Z", "Fixed a typo and "
			"updated the description.");
  h.description("Private DEMO MIB.");
}


// (2) --- The structure of this MIB. Compare with VTSS-DEMO-MIB.mib
//
// demo_root---demo_mib_objects(1)-+-demo_status(1)-+-DemoEx1(1)-+-Attr1(1)
//                                 |                |            |
//                                 |                |            +-Attr2(2)
//                                 |                |
//                                 |                +-DemoEx2(2)---Attr(1)
//                                 |
//                                 |
//                                 +-demo_trap(2)-----DemoEx2Trap(1)
//
// The DemoEx1(1) attribute is a set of two attributes.
//
// The DemoEx2 consists of DemoEx2(2) and DemoEx2Trap(1). The first
// represent the value of the attribute and the second a trap assoicated with it.
//
// Example 3 etc are not shown in this table.
//
// The SNMP MIB can be seen in a browser with http://A.B.C.D/VTSS-DEMO-MIB.mib
//


#define NS(VAR, P, ID, NAME) static NamespaceNode VAR(&P, OidElement(ID, NAME))


// (3) --- The macro, which is defined above, are used to build up a tree from the bottom up.
//
NS(demo_mib_objects, demo_root, 1, "DemoMibObjects");

NS(demo_status,    demo_mib_objects, 1, "DemoStatus");
NS(demo_trap,      demo_mib_objects, 2, "DemoTrap");


// (4) --- Simple read/write attribute
//
static StructRW2<DemoEx1>       _demo_ex1(
     &demo_status, expose::snmp::OidElement(1, "DemoEx1"));


// (5) --- A read-only integer that is associated with a trap. The
//         value can be changed with demo_attribute.cxx::demo_ex2_generate_trap(),
//         which is called if the ICLI commands 'demo trap <value>' is called.
//
static StructRoTrap<DemoEx2>    _demo_ex2(
     &demo_status, expose::snmp::OidElement(2, "DemoEx2"),
     &demo_trap,   expose::snmp::OidElement(20, "DemoEx2Trap"), &demo_ex2);


// (6) --- Table of integers with a integer index
//
static TableReadWrite2<DemoEx3> _demo_ex3(
    &demo_status, expose::snmp::OidElement(3, "DemoEx3Table"));


// (7) --- Table of integers with a ifIndex as index. Compare to Ex3
//
static TableReadWrite2<DemoEx4> _demo_ex4(
    &demo_status, expose::snmp::OidElement(4, "DemoEx4Table"));


// (8) --- Table of integers with 3 integer indexes. Compare to Ex3. The only
//         difference is that an iterator works in 3 numbers. The idea is to
//         define an iterator for each index and then compine then to a "master"
//         iterator.
//
static TableReadWrite2<DemoEx5> _demo_ex5(
    &demo_status, expose::snmp::OidElement(5, "DemoEx5Table"));

// (9) --- Table that is read-only from SNMP, that emit traps when changes happen.
//
static TableReadOnlyTrap<DemoEx6>        _demo_ex6(
    &demo_status, expose::snmp::OidElement(6, "DemoEx6Table"),
    &demo_ex6_status,
    &demo_trap, "DemoEx6Trap", expose::snmp::OidElement(60, "DemoEx6TrapAdd"),
                               expose::snmp::OidElement(61, "DemoEx6TrapMod"),
                               expose::snmp::OidElement(63, "DemoEx6TrapDel"));

// (10) --- Table that is read-write.
//
static TableReadWriteAddDelete2<DemoEx7> _demo_ex7(
    &demo_status, expose::snmp::OidElement(70, "DemoEx7Table"),
                  expose::snmp::OidElement(71, "DemoEx7TableRowEditor"));
