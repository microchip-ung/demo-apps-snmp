#ifndef _DEMO_ATTRIBUTES_H_
#define _DEMO_ATTRIBUTES_H_

//#include <mscc/ethernet/switch/api/types.h>
#include <vtss/appl/interface.h>
#include <vtss/basics/enum-descriptor.h>
#include <vtss/basics/expose.hxx>

#ifdef __cplusplus
extern "C" {
#endif

  // (1) --- Example 1: Simple get/set attribute

  typedef struct {
    mesa_bool_t  attr1;
    uint32_t     attr2;
  } demo_ex1_attr_t;

  mesa_rc demo_ex1_set(const demo_ex1_attr_t  *const a);
  mesa_rc demo_ex1_get(demo_ex1_attr_t  *const a);

  
  // (2) --- Example 2: ReadOnly trap attribute. The type of the attribute is int, so we
  //         do not define a structure. There is no set function, since the attribute
  //         is read-only from a MIB perspective.

#if 1

  class demo_ex2_attr_t {
  public:
    int i;
  };
  bool operator!=(const demo_ex2_attr_t& x, const demo_ex2_attr_t& y);

#else

  typedef int demo_ex2_attr_t;

#endif
  
  mesa_rc demo_ex2_get(demo_ex2_attr_t  *const a);


  // (3) --- Example 3: A table

  typedef int demo_ex3_index_t;

  typedef struct {
    int attr1_ex3;
    int attr2_ex3;
  } demo_ex3_attr_t;
  

  mesa_rc demo_ex3_set(demo_ex3_index_t  index,
		       const demo_ex3_attr_t  *const a);

  mesa_rc demo_ex3_get(demo_ex3_index_t  index,
		       demo_ex3_attr_t  *const a);
  
  mesa_rc demo_ex3_itr(const demo_ex3_index_t  *prev_index,
		       demo_ex3_index_t        *next_index);


  // (4) --- Example 4: A table

  typedef struct {
    int attr1_ex4;
    int attr2_ex4;
  } demo_ex4_attr_t;
  

  mesa_rc demo_ex4_set(vtss_ifindex_t  ifindex,
		       const demo_ex4_attr_t  *const a);

  mesa_rc demo_ex4_get(vtss_ifindex_t  ifindex,
		       demo_ex4_attr_t  *const a);
  
  mesa_rc demo_ex4_itr(const vtss_ifindex_t  *prev_ifindex,
		       vtss_ifindex_t        *next_ifindex);


  // (5) --- Example 5: A table with 3 indexes

  typedef int demo_ex5_index1_t;
  typedef int demo_ex5_index2_t;
  typedef int demo_ex5_index3_t;
  
  typedef struct {
    int attr1_ex5;
    int attr2_ex5;
  } demo_ex5_attr_t;

  mesa_rc demo_ex5_set(demo_ex5_index1_t  i1,
		       demo_ex5_index2_t  i2,
		       demo_ex5_index3_t  i3,
		       const demo_ex5_attr_t  *const a);

  mesa_rc demo_ex5_get(demo_ex5_index1_t  i1,
		       demo_ex5_index2_t  i2,
		       demo_ex5_index3_t  i3,
		       demo_ex5_attr_t  *const a);
  
  mesa_rc demo_ex5_itr(const demo_ex5_index1_t  *prev_i1,
		       demo_ex5_index1_t        *next_i1,
		       const demo_ex5_index2_t  *prev_i2,
		       demo_ex5_index2_t        *next_i2,
		       const demo_ex5_index3_t  *prev_i3,
		       demo_ex5_index3_t        *next_i3);


#if 1
  // (6) --- Example 6: A table with 1 index and trap
  
  typedef int demo_ex6_index_t;

  typedef struct {
    uint32_t attr1_ex6;
    uint32_t attr2_ex6;
  } demo_ex6_attr_t;

  mesa_rc demo_ex6_set(demo_ex6_index_t  index,
		       const demo_ex6_attr_t  *const a);

  mesa_rc demo_ex6_get(demo_ex6_index_t  index,
		       demo_ex6_attr_t  *const a);
  
  mesa_rc demo_ex6_itr(const demo_ex6_index_t  *prev_index,
		       demo_ex6_index_t        *next_index);

#endif

  // (7) --- Example 7: A read/write/add/delete table with 1 index.
  typedef int demo_ex7_index_t;

  typedef struct {
    uint32_t attr1_ex7;
    uint32_t attr2_ex7;
  } demo_ex7_attr_t;

  mesa_rc demo_ex7_get(demo_ex7_index_t  i,
		       demo_ex7_attr_t  *const a);

  mesa_rc demo_ex7_set(demo_ex7_index_t  i,
		       const demo_ex7_attr_t  *const a);

  mesa_rc demo_ex7_add(demo_ex7_index_t  i,
		       const demo_ex7_attr_t  *const a);

  mesa_rc demo_ex7_itr(const demo_ex7_index_t  *prev_i,
		       demo_ex7_index_t        *next_i);

  mesa_rc demo_ex7_del(demo_ex7_index_t  i);

  mesa_rc demo_ex7_def(demo_ex7_index_t *index, demo_ex7_attr_t *value);

#ifdef __cplusplus
}
#endif


extern vtss::expose::StructStatus<vtss::expose::ParamVal<demo_ex2_attr_t *>> demo_ex2;

extern vtss::expose::TableStatus<vtss::expose::ParamKey<demo_ex6_index_t>,
                                 vtss::expose::ParamVal<demo_ex6_attr_t *>> demo_ex6_status;

#endif  // _DEMO_ATTRIBUTES_H_
