#include "demo_serializer.hxx"
#include "vtss/basics/expose/json.hxx"


using namespace vtss;
using namespace vtss::json;
using namespace vtss::expose::json;
using namespace vtss::demo;


namespace vtss {
  void json_node_add(Node *node);
}

static NamespaceNode demo_root("demo");

// (1) --- This function is called from demo.cxx in order to register this
//         demo json tree.
//
extern "C" void demo_json_init()
{
    json_node_add(&demo_root);
}

// (2) --- The code structure below is similar to the SNMP version. So
//         for a description look in demo_mib.cxx


#define NS(N, P, D) static vtss::expose::json::NamespaceNode N(&P, D);


NS(demo_config, demo_root, "something");

static StructReadWrite<DemoEx1>             _demo_ex1(
     &demo_config, "simple_ex1");

static StructReadOnlyNotification<DemoEx2>  _demo_ex2(
     &demo_config, "notif_ex2", &demo_ex2);

static TableReadWrite<DemoEx3>              _demo_ex3(
     &demo_config, "table_ex3");

static TableReadWrite<DemoEx4>              _demo_ex4(
     &demo_config, "table_ex4");

static TableReadWrite<DemoEx5>              _demo_ex5(
     &demo_config, "table_ex5");

static TableReadOnlyNotification<DemoEx6>   _demo_ex6(
     &demo_config, "table_ex6", &demo_ex6_status);

#if 1 // With or without (NoNS) namespace

static TableReadWriteAddDelete<DemoEx7> _demo_ex7(
     &demo_config, "table_ex7");

#else

static TableReadWriteAddDeleteNoNS<DemoEx7> _demo_ex7(
     &demo_config);

#endif

// In order to test the json interface, it is suggested to use the vson tools that
// can be downloaded with
//
// $ git clone https://github.com/vtss/json-rpc-util.git
//
// Then run
// $ ./vson -d <target-IP-address> -c update-spec
// and then
// $ ./vson -d <target-IP-address> -c grep demo
// Then you will get a list of all json commands that contain the string "demo".
// With the abobe code you should get
//
// demo.something.simple_ex1.get
// demo.something.simple_ex1.set
// demo.something.notif_ex2.get
// demo.something.table_ex3.get
// demo.something.table_ex3.get
// demo.something.table_ex3.set
// demo.something.table_ex4.get
// demo.something.table_ex4.get
// demo.something.table_ex4.set
// demo.something.table_ex5.get
// demo.something.table_ex5.get
// demo.something.table_ex5.set
// demo.something.table_ex6.get
// demo.something.table_ex6.get
// demo.something.table_ex7.get
// demo.something.table_ex7.get
// demo.something.table_ex7.set
// demo.something.table_ex7.add
// demo.something.table_ex7.del
//
// To test it you can e.g. say
// $ ./vson -d <target-IP-address> -c call demo.something.table_ex3.get
// Calling demo.something.table_ex3.get:
//     key Attr1_Ex3 Attr2_Ex3 
//     --- --------- --------- 
//       0         0         0 
//       1         1         2 
//       2         2         4 
//       3         3         6 
//       4         4         8 
//       5         5        10 
// 
