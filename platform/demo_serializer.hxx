#ifndef __DEMO_SERIALIZER_HXX__
#define __DEMO_SERIALIZER_HXX__

#include "vtss_appl_serialize.hxx"
#include "demo_attributes.h"


// (1) --- Define serializers for all the attribute sutctures in demo_attribute.h


// (1.1) --- Serializer for demo_ex1_attr_t
//
template <typename T>
void serialize(T &h, demo_ex1_attr_t &p)
{
    typename T::Map_t m = h.as_map(vtss::tag::Typename("demo_ex1_attr_t"));

    // Due to the call h.argument_properties(vtss::expose::snmp::OidOffset(1))
    // done prior by the caller, the numbering of the OID start at 1.
    //
    int oid = 0;

    m.add_leaf(vtss::AsBool(p.attr1),
	       vtss::tag::Name("Attr1"),
	       vtss::expose::snmp::Status::Current,
	       vtss::expose::snmp::OidElementValue(oid++),
	       vtss::tag::Description("Attribute 1 which is a boolean"
				      "TRUE - something, FALSE - something else.")
	       );

    m.add_leaf(vtss::AsInt(p.attr2),
	       vtss::tag::Name("Attr2"),
	       vtss::expose::snmp::Status::Current,
	       vtss::expose::snmp::OidElementValue(oid++),
	       vtss::tag::Description("Attribute 2 is an uint32")
	       );

}


// (1.2) --- Serializer for demo_ex2_attr_t
//
template <typename T>
void serialize(T &h, demo_ex2_attr_t &i)
{
    typename T::Map_t m = h.as_map(vtss::tag::Typename("demo_ex2_attr_t"));

    m.add_leaf(i.i, vtss::tag::Name("aaaa"), vtss::expose::snmp::OidElementValue(10),
	       vtss::tag::Description("bbbb"));

}


// (1.3) --- Serializer for demo_ex3_attr_t

VTSS_SNMP_TAG_SERIALIZE(demo_ex3_index, demo_ex3_index_t, m, s)
{
    m.add_leaf(
	       s.inner,
	       vtss::tag::Name("Index3"),
	       vtss::expose::snmp::Status::Current,
	       vtss::expose::snmp::OidElementValue(0),
	       vtss::tag::Description("The index of logical interface.")
    );
}


template <typename T>
void serialize(T &h, demo_ex3_attr_t &p)
{
    typename T::Map_t m = h.as_map(vtss::tag::Typename("demo_ex3_attr_t"));

    // Due to the call h.argument_properties(vtss::expose::snmp::OidOffset(1))
    // done prior by the caller, the numbering of the OID start at 1.
    //
    int oid = 0;

    m.add_leaf(p.attr1_ex3,
	       vtss::tag::Name("Attr1_Ex3"),
	       vtss::expose::snmp::Status::Current,
	       vtss::expose::snmp::OidElementValue(oid++),
	       vtss::tag::Description("Attribute 1 which is an int")
	       );

    m.add_leaf(p.attr2_ex3,
	       vtss::tag::Name("Attr2_Ex3"),
	       vtss::expose::snmp::Status::Current,
	       vtss::expose::snmp::OidElementValue(oid++),
	       vtss::tag::Description("Attribute 2 is an uint32")
	       );

}


// (1.4) --- Serializer for demo_ex4_attr_t

template <typename T>
void serialize(T &h, demo_ex4_attr_t &i)
{
    typename T::Map_t m = h.as_map(vtss::tag::Typename("demo_ex4_attr_t"));

    m.add_leaf(i.attr1_ex4, vtss::tag::Name("aaa1a"), vtss::expose::snmp::OidElementValue(10),
	       vtss::tag::Description("bbb1b"));

    m.add_leaf(i.attr2_ex4, vtss::tag::Name("aaa2a"), vtss::expose::snmp::OidElementValue(11),
	       vtss::tag::Description("bbb2b"));

}

VTSS_SNMP_TAG_SERIALIZE(demo_ifindex_index, vtss_ifindex_t, m, s)
{
    m.add_leaf(
        vtss::AsInterfaceIndex(s.inner),
        vtss::tag::Name("IfIndex"),
        vtss::expose::snmp::Status::Current,
        vtss::expose::snmp::OidElementValue(0),
        vtss::tag::Description("The index of logical interface.")
    );
}


// (1.5) --- Serializer for demo_ex5_attr_t

VTSS_SNMP_TAG_SERIALIZE(demo_ex5_index1, demo_ex5_index1_t, m, s)
{
    m.add_leaf(
	       s.inner,
	       vtss::tag::Name("I1"),
	       vtss::expose::snmp::Status::Current,
	       vtss::expose::snmp::OidElementValue(0),
	       vtss::tag::Description("The index of logical interface.")
    );
}

VTSS_SNMP_TAG_SERIALIZE(demo_ex5_index2, demo_ex5_index2_t, m, s)
{
    m.add_leaf(
	       s.inner,
	       vtss::tag::Name("I2"),
	       vtss::expose::snmp::Status::Current,
	       vtss::expose::snmp::OidElementValue(0),
	       vtss::tag::Description("The index of logical interface.")
    );
}

VTSS_SNMP_TAG_SERIALIZE(demo_ex5_index3, demo_ex5_index3_t, m, s)
{
    m.add_leaf(
	       s.inner,
	       vtss::tag::Name("I3"),
	       vtss::expose::snmp::Status::Current,
	       vtss::expose::snmp::OidElementValue(0),
	       vtss::tag::Description("The index of logical interface.")
    );
}

template <typename T>
void serialize(T &h, demo_ex5_attr_t &p)
{
    typename T::Map_t m = h.as_map(vtss::tag::Typename("demo_ex5_attr_t"));

    // Due to the call h.argument_properties(vtss::expose::snmp::OidOffset(1))
    // done prior by the caller, the numbering of the OID start at 1.
    //
    int oid = 0;

    m.add_leaf(p.attr1_ex5,
	       vtss::tag::Name("Attr1_Ex5"),
	       vtss::expose::snmp::Status::Current,
	       vtss::expose::snmp::OidElementValue(oid++),
	       vtss::tag::Description("Attribute 1 which is an int")
	       );

    m.add_leaf(p.attr2_ex5,
	       vtss::tag::Name("Attr2_Ex5"),
	       vtss::expose::snmp::Status::Current,
	       vtss::expose::snmp::OidElementValue(oid++),
	       vtss::tag::Description("Attribute 2 is an uint32")
	       );

}



// (1.6) --- Serializer for demo_ex6_attr_t

VTSS_SNMP_TAG_SERIALIZE(demo_ex6_index, demo_ex6_index_t, m, s)
{
    m.add_leaf(
	       s.inner,
	       vtss::tag::Name("Index"),
	       vtss::expose::snmp::Status::Current,
	       vtss::expose::snmp::OidElementValue(0),
	       vtss::tag::Description("The index of logical interface.")
    );
}


template <typename T>
void serialize(T &h, demo_ex6_attr_t &p)
{
    typename T::Map_t m = h.as_map(vtss::tag::Typename("demo_ex6_attr_t"));

    // Due to the call h.argument_properties(vtss::expose::snmp::OidOffset(1))
    // done prior by the caller, the numbering of the OID start at 1.
    //
    int oid = 0;

    m.add_leaf(p.attr1_ex6,
	       vtss::tag::Name("Attr1_Ex6"),
	       vtss::expose::snmp::Status::Current,
	       vtss::expose::snmp::OidElementValue(oid++),
	       vtss::tag::Description("Attribute 1 which is an int")
	       );

    m.add_leaf(p.attr2_ex6,
	       vtss::tag::Name("Attr2_Ex6"),
	       vtss::expose::snmp::Status::Current,
	       vtss::expose::snmp::OidElementValue(oid++),
	       vtss::tag::Description("Attribute 2 is an uint32")
	       );

}


// (1.7) --- Serializer for demo_ex7_attr_t

VTSS_SNMP_TAG_SERIALIZE(demo_ex7_index, demo_ex7_index_t, m, s)
{
    m.add_leaf(
	       s.inner,
	       vtss::tag::Name("Index"),
	       vtss::expose::snmp::Status::Current,
	       vtss::expose::snmp::OidElementValue(0),
	       vtss::tag::Description("The index of logical interface.")
    );
}


template <typename T>
void serialize(T &h, demo_ex7_attr_t &p)
{
    typename T::Map_t m = h.as_map(vtss::tag::Typename("demo_ex7_attr_t"));

    // Due to the call h.argument_properties(vtss::expose::snmp::OidOffset(1))
    // done prior by the caller, the numbering of the OID start at 1.
    //
    int oid = 0;

    m.add_leaf(p.attr1_ex7,
	       vtss::tag::Name("Attr1_Ex7"),
	       vtss::expose::snmp::Status::Current,
	       vtss::expose::snmp::OidElementValue(oid++),
	       vtss::tag::Description("Attribute 1 which is an int")
	       );

    m.add_leaf(p.attr2_ex7,
	       vtss::tag::Name("Attr2_Ex7"),
	       vtss::expose::snmp::Status::Current,
	       vtss::expose::snmp::OidElementValue(oid++),
	       vtss::tag::Description("Attribute 2 is an uint32")
	       );

}



// (2) --- Define interface structures for exposure by MIB, JSON etc

namespace vtss {
  namespace demo {

    // (2.1.1) --- Define the type P.
    //
    // (2.1.2) --- Define template function:
    //
    // template <typename HANDLER>
    //  void argument(HANDLER &h, ::vtss::expose::arg::_1, vtss_appl_demo_t &i)
    //
    // So h must have a member argument_properties() and the template function
    // serialize(HANDLER &h, vtss_appl_gvrp_config_globals_t &i) must exist.
    //
    // (2.1.3) --- Define function handlers. This require the P type above
    //
    // #define VTSS_EXPOSE_GET_PTR(X) static constexpr typename P::get_t get = &X


    // The DemoEx1 type provide the interface to accessing the attributes in question.
    // This type is used in:
    //  demo_mib.cxx  for SNMP access
    //  demo_json.cxx for json access
    //
    struct DemoEx1
    {
      typedef expose::ParamList<expose::ParamVal<demo_ex1_attr_t *>>  P;
      
      // Define argument() template function.
      VTSS_EXPOSE_SERIALIZE_ARG_1(demo_ex1_attr_t &i)
      {
	// See the serializer() below for the reason behind the call.
	h.argument_properties(vtss::expose::snmp::OidOffset(1));

	// Defined above as a template function
	serialize(h, i);
      }

      VTSS_EXPOSE_GET_PTR(demo_ex1_get);
      VTSS_EXPOSE_SET_PTR(demo_ex1_set);
      //      VTSS_EXPOSE_WEB_PRIV(VTSS_PRIV_LVL_CONFIG_TYPE, VTSS_MODULE_ID_DEMO_SNMP);
      
    };


    // (2.2) --- Example 2: Trap example
    //
    //           Compare with VTSS-DEMO-MIB.mib how the names 'aaaa', 'bbbb' and
    //           OidElementValue(10) manifest itself.
    //
    struct DemoEx2 {
      typedef expose::ParamList<expose::ParamVal<demo_ex2_attr_t *>> P;

      static constexpr const char *rpc_description = "asdfasdf";

      VTSS_EXPOSE_SERIALIZE_ARG_1(demo_ex2_attr_t &i)
      {
	serialize(h, i);
      }

      static constexpr const char *desc_get_func = "get-ptr";
      VTSS_EXPOSE_GET_PTR(demo_ex2_get);
    };


    // (2.3) --- Example 3: Table example
    //
    struct DemoEx3 {

      // This table has an index represented by the type 'demo_ex3_index_t' and
      // is the 1st argument to the ParamList template via the ParamKey template.
      //
      // The values in the table is represented by the 'demo_ex3_attr_t' adn is
      // the 2nd argument to ParamList via ParamVal
      typedef vtss::expose::ParamList <
	 vtss::expose::ParamKey<demo_ex3_index_t>,    // ARG_1
	 vtss::expose::ParamVal<demo_ex3_attr_t *>    // ARG_2
	> P;

      static constexpr const char *table_description =
        "This is a demonstration of the simples posible table. "
	"It uses an integer as index, and each table item contains two numbers.";

      static constexpr const char *index_description =
        "The index is a number 0,...,5 in that order.";

      VTSS_EXPOSE_SERIALIZE_ARG_1(demo_ex3_index_t &i)
      {
        h.argument_properties(vtss::expose::snmp::OidOffset(1));
        serialize(h, demo_ex3_index(i));
      }

      VTSS_EXPOSE_SERIALIZE_ARG_2(demo_ex3_attr_t &i)
      {
        h.argument_properties(vtss::expose::snmp::OidOffset(2));
        serialize(h, i);
      }

      VTSS_EXPOSE_ITR_PTR(demo_ex3_itr);
      VTSS_EXPOSE_GET_PTR(demo_ex3_get);
      VTSS_EXPOSE_SET_PTR(demo_ex3_set);
      //    VTSS_EXPOSE_WEB_PRIV(VTSS_PRIV_LVL_CONFIG_TYPE, VTSS_MODULE_ID_DEMO_SNMP);
    };


    // (2.4) --- Example 4: Table example
    //
    struct DemoEx4 {
      typedef vtss::expose::ParamList <
	 vtss::expose::ParamKey<vtss_ifindex_t>,    // ARG_1
	 vtss::expose::ParamVal<demo_ex4_attr_t *>  // ARG_2
	> P;

      static constexpr const char *table_description =
        "This is demonstration of a table that use ifIndex as index";

      static constexpr const char *index_description =
        "Each interface has a set of parameters";

      VTSS_EXPOSE_SERIALIZE_ARG_1(vtss_ifindex_t &i)
      {
        h.argument_properties(vtss::expose::snmp::OidOffset(1));
        serialize(h, demo_ifindex_index(i));
      }

      VTSS_EXPOSE_SERIALIZE_ARG_2(demo_ex4_attr_t &i)
      {
        h.argument_properties(vtss::expose::snmp::OidOffset(2));
        serialize(h, i);
      }

      VTSS_EXPOSE_ITR_PTR(demo_ex4_itr);
      VTSS_EXPOSE_GET_PTR(demo_ex4_get);
      VTSS_EXPOSE_SET_PTR(demo_ex4_set);
      //    VTSS_EXPOSE_WEB_PRIV(VTSS_PRIV_LVL_CONFIG_TYPE, VTSS_MODULE_ID_DEMO_SNMP);
    };


    // (2.5) --- Example 5: Table with 3 indexes 
    //
    struct DemoEx5 {

      // We want 3 indexes to our table, i.e. 3 keys
      //
      typedef vtss::expose::ParamList <
	 vtss::expose::ParamKey<demo_ex5_index1_t>,    // ARG_1
	 vtss::expose::ParamKey<demo_ex5_index2_t>,    // ARG_2
	 vtss::expose::ParamKey<demo_ex5_index3_t>,    // ARG_3
	 vtss::expose::ParamVal<demo_ex5_attr_t *>     // ARG_4
	> P;

      static constexpr const char *table_description =
        "This is demonstration of a table that use ifIndex as index";

      static constexpr const char *index_description =
        "Each interface has a set of parameters";

      VTSS_EXPOSE_SERIALIZE_ARG_1(demo_ex5_index1_t &i1)
      {
        h.argument_properties(vtss::expose::snmp::OidOffset(1));
        serialize(h, demo_ex5_index1(i1));
      }

      VTSS_EXPOSE_SERIALIZE_ARG_2(demo_ex5_index2_t &i2)
      {
        h.argument_properties(vtss::expose::snmp::OidOffset(2));
        serialize(h, demo_ex5_index2(i2));
      }

      VTSS_EXPOSE_SERIALIZE_ARG_3(demo_ex5_index3_t &i3)
      {
        h.argument_properties(vtss::expose::snmp::OidOffset(3));
        serialize(h, demo_ex5_index3(i3));
      }

      
      VTSS_EXPOSE_SERIALIZE_ARG_4(demo_ex5_attr_t &v)
      {
        h.argument_properties(vtss::expose::snmp::OidOffset(4));
        serialize(h, v);
      }

      VTSS_EXPOSE_ITR_PTR(demo_ex5_itr);
      VTSS_EXPOSE_GET_PTR(demo_ex5_get);
      VTSS_EXPOSE_SET_PTR(demo_ex5_set);
      //    VTSS_EXPOSE_WEB_PRIV(VTSS_PRIV_LVL_CONFIG_TYPE, VTSS_MODULE_ID_DEMO_SNMP);
    };


    // (2.6) --- Example 6: Table with 1 index and traps 
    //
    struct DemoEx6 {
      typedef expose::ParamList<expose::ParamKey<demo_ex6_index_t>,
				expose::ParamVal<demo_ex6_attr_t *>
       > P;

      static constexpr const char *table_description =
	"This table provides link-layer status information for IP "
	"interfaces.";

      static constexpr const char *index_description =
	"Each entry in this table represents an IP interface.";

      VTSS_EXPOSE_SERIALIZE_ARG_1(demo_ex6_index_t &i) {
        h.argument_properties(tag::Name("ifidx"));
        serialize(h, demo_ex7_index(i));
      }

      VTSS_EXPOSE_SERIALIZE_ARG_2(demo_ex6_attr_t &i) {
        h.argument_properties(tag::Name("status"));
        h.argument_properties(expose::snmp::OidOffset(1));
        serialize(h, i);
      }

      VTSS_EXPOSE_WEB_PRIV(VTSS_PRIV_LVL_STAT_TYPE, VTSS_MODULE_ID_DEMO_SNMP);
    };


    // (2.7) --- Example 7: Table with 1 index
    //
    struct DemoEx7 {
      typedef expose::ParamList<
	expose::ParamKey<demo_ex7_index_t>,  // ARG_1
	expose::ParamVal<demo_ex7_attr_t *>  // ARG_2
      > P;

      // Specify the OID of the action attribute
      //
      static constexpr uint32_t snmpRowEditorOid = 123;

      static constexpr const char *table_description =
	"Example 7 table description.";

      static constexpr const char *index_description =
	"Example 7 index description.";

      VTSS_EXPOSE_SERIALIZE_ARG_1(demo_ex7_index_t &i) {
        h.argument_properties(tag::Name("ex7-index"));
        h.argument_properties(expose::snmp::OidOffset(1));
        serialize(h, demo_ex7_index(i));
      }

      VTSS_EXPOSE_SERIALIZE_ARG_2(demo_ex7_attr_t &i) {
        h.argument_properties(tag::Name("ex7-value"));
        h.argument_properties(expose::snmp::OidOffset(2));
        serialize(h, i);
      }

      VTSS_EXPOSE_GET_PTR(demo_ex7_get);
      VTSS_EXPOSE_ITR_PTR(demo_ex7_itr);
      VTSS_EXPOSE_SET_PTR(demo_ex7_set);
      VTSS_EXPOSE_ADD_PTR(demo_ex7_add);
      VTSS_EXPOSE_DEL_PTR(demo_ex7_del);
      VTSS_EXPOSE_DEF_PTR(demo_ex7_def);
      VTSS_EXPOSE_WEB_PRIV(VTSS_PRIV_LVL_CONFIG_TYPE, VTSS_MODULE_ID_DEMO_SNMP);
    };

  } // demo namespace
} // vtss namespace


#endif // __DEMO_SERIALIZER_HXX__
