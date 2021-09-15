#include "demo_attributes.h"

#include <vtss_trace_api.h>
#include "critd_api.h"
#include <vtss/basics/expose.hxx>
#include "vtss_appl_serialize.hxx"
#include "vtss/appl/interface.h"

#define VTSS_TRACE_MODULE_ID VTSS_MODULE_ID_DEMO_SNMP
#define VTSS_ALLOC_MODULE_ID VTSS_MODULE_ID_DEMO_SNMP


// (1) ------ Example 1 ------


static demo_ex1_attr_t ex1_attr;

mesa_rc demo_ex1_get(demo_ex1_attr_t  *const a)
{
    /* Check illegal parameters */
    if (!a) {
      T_W("Input parameter is NULL");
      return VTSS_RC_ERROR;
    }

    a->attr1 = ex1_attr.attr1;
    a->attr2 = ex1_attr.attr2;

    return VTSS_RC_OK;
}


mesa_rc demo_ex1_set(const demo_ex1_attr_t  *const a)
{
    /* Check illegal parameters */
    if (!a) {
        T_W("Input parameter is NULL");
        return VTSS_RC_ERROR;
    }

    // Store the values
    ex1_attr = *a;

    return VTSS_RC_OK;
}


// (2) ------ Example 2 ------


vtss::expose::StructStatus<vtss::expose::ParamVal<demo_ex2_attr_t *>> demo_ex2;

mesa_rc demo_ex2_get(demo_ex2_attr_t  *const a)
{
  if (!a) return VTSS_RC_ERROR;
  return demo_ex2.get(a);
}

void demo_ex2_generate_trap(int x)
{
  demo_ex2_attr_t a;
  a.i=x;
  // Setting the value from the system will generate a SNMP trap.
  // Do that with ICLI commands 'demo trap 1'.
  //
  demo_ex2.set(&a);
}

bool operator!=(const demo_ex2_attr_t& x, const demo_ex2_attr_t& y)
{
  return x.i!=y.i;
}


// (3) ------ Example 3 ------


mesa_rc demo_ex3_set(demo_ex3_index_t  index,
		     const demo_ex3_attr_t  *const a)
{
  // We will just print out the set values,
  // and skip actually to save the values.
  //
  printf("%s index=%d value=(%d,%d)\n",
	 __FUNCTION__,
	 index,
	 a->attr1_ex3, a->attr2_ex3);

  return VTSS_RC_OK;
}

mesa_rc demo_ex3_get(demo_ex3_index_t  index,
		     demo_ex3_attr_t  *const a)
{
  // Just return i1+i2 in attr1 and i2+i3 in attr2
  a->attr1_ex3 = index;
  a->attr2_ex3 = index*2;

  return VTSS_RC_OK;
}

mesa_rc demo_ex3_itr(const demo_ex3_index_t  *prev_index,
		     demo_ex3_index_t        *next_index)
{
  // -If prev_index is NULL, then return first index in *next_iindex and return VTSS_RC_OK.
  // -If prev_index is not NULL and *prev_i1 is not the last index, then
  //  return the next index in *next_iindex and return VTSS_RC_OK.
  // -If prev_index is not NULL and *prev_index is the last index, then return VTSS_RC_ERROR.

  // We iterate over the numbers 0,...,5
  //
  if (!prev_index)  *next_index=0;
  else if (*prev_index<5) *next_index = *prev_index + 1;
  else return VTSS_RC_ERROR;

  return VTSS_RC_OK;
}


// (4) ------ Example 4 ------


// Put the ifindex to something mapping in a function, since the same code
// is needed by set and get
//
static mesa_rc demo_ex4_index(vtss_ifindex_t  ifindex, uint32_t *ordinal)
{
  mesa_rc  rc;
  vtss_ifindex_elm_t  ife;

  //  printf("%s ifIndex=%u\n", __FUNCTION__, ifindex.private_ifindex_data_do_not_use_directly);
  
  rc = vtss_appl_ifindex_port_configurable(ifindex, &ife);
  if (rc) return rc;

  *ordinal = ife.ordinal;

  return rc;
}

mesa_rc demo_ex4_set(vtss_ifindex_t  ifindex,
		     const demo_ex4_attr_t  *const a)
{
  mesa_rc  rc=VTSS_RC_ERROR;
  uint32_t  ordinal;

  if (!a) return rc;
  
  rc = demo_ex4_index(ifindex, &ordinal);
  if (rc) return rc;

  printf("%s ordinal=%u\n", __FUNCTION__, ordinal);

  return rc;
}

mesa_rc demo_ex4_get(vtss_ifindex_t  ifindex,
		     demo_ex4_attr_t  *const a)
{
  mesa_rc  rc=VTSS_RC_ERROR;
  uint32_t  ordinal;
  
  if (!a) return rc;
  
  rc = demo_ex4_index(ifindex, &ordinal);
  if (rc) return rc;

  printf("%s ordinal=%u\n", __FUNCTION__, ordinal);

  a->attr1_ex4 = (int)ordinal;
  a->attr2_ex4 = (int)ordinal*7;
  
  return rc;
}


mesa_rc demo_ex4_itr(const vtss_ifindex_t  *prev_ifindex,
		     vtss_ifindex_t        *next_ifindex)
{
  mesa_rc  rc;
  rc = vtss_appl_iterator_ifindex_front_port(prev_ifindex, next_ifindex);

#if 1
  printf("%s prev=%u next=%u\n", __FUNCTION__,
	 prev_ifindex ? prev_ifindex->private_ifindex_data_do_not_use_directly : -1,
	 next_ifindex ? next_ifindex->private_ifindex_data_do_not_use_directly : -1);
#endif
  return rc;
}


// (5) ------ Example 5 ------


mesa_rc demo_ex5_set(demo_ex5_index1_t  i1,
		     demo_ex5_index2_t  i2,
		     demo_ex5_index3_t  i3,
		     const demo_ex5_attr_t  *const a)
{
  // We will just print out the set values, and skip actually to save the values.

  printf("%s index=(%d,%d,%d) value=(%d,%d)\n",
	 __FUNCTION__,
	 i1, i2, i3,
	 a->attr1_ex5, a->attr2_ex5);

  return VTSS_RC_OK;
}

mesa_rc demo_ex5_get(demo_ex5_index1_t  i1,
		     demo_ex5_index2_t  i2,
		     demo_ex5_index3_t  i3,
		     demo_ex5_attr_t  *const a)
{
  // Just return i1+i2 in attr1 and i2+i3 in attr2
  a->attr1_ex5 = i1+i2;
  a->attr2_ex5 = i2+i3;

  return VTSS_RC_OK;
}

// The iterator: One iterator for each index is provided, and then all 3 are aggregated
// into one in the demo_ex5_itr() below
//
static mesa_rc demo_ex5_i1_itr(const demo_ex5_index1_t  *prev_i1,
			demo_ex5_index1_t        *next_i1)
{
  //  If prev_i1 is NULL, then return first index in *next_i1 and return VTSS_RC_OK.
  //  If prev_i1 is not NULL and *prev_i1 is not the last index, then
  // return the next index in *next_i1 and return VTSS_RC_OK.
  //  If prev_i1 is not NULL and *prev_i1 is the last index, then return VTSS_RC_ERROR.
  //
  if (!prev_i1)  *next_i1=0;
  else if (*prev_i1<5) *next_i1 = *prev_i1 + 1;
  else return VTSS_RC_ERROR;

  return VTSS_RC_OK;
}


static mesa_rc demo_ex5_i2_itr(const demo_ex5_index2_t  *prev_i2,
			demo_ex5_index2_t        *next_i2)
{
  if (!prev_i2)  *next_i2=0;
  else if (*prev_i2<5) *next_i2 = *prev_i2 + 1;
  else return VTSS_RC_ERROR;

  return VTSS_RC_OK;
}


static mesa_rc demo_ex5_i3_itr(const demo_ex5_index3_t  *prev_i3,
			demo_ex5_index3_t        *next_i3)
{
  if (!prev_i3)  *next_i3=0;
  else if (*prev_i3<5) *next_i3 = *prev_i3 + 1;
  else return VTSS_RC_ERROR;

  return VTSS_RC_OK;
}


mesa_rc demo_ex5_itr(const demo_ex5_index1_t  *prev_i1,
		     demo_ex5_index1_t        *next_i1,
		     const demo_ex5_index1_t  *prev_i2,
		     demo_ex5_index1_t        *next_i2,
		     const demo_ex5_index1_t  *prev_i3,
		     demo_ex5_index1_t        *next_i3)
{
  vtss::IteratorComposeN<demo_ex5_index1_t,
			 demo_ex5_index2_t,
			 demo_ex5_index3_t> itr(demo_ex5_i1_itr,
						demo_ex5_i2_itr,
						demo_ex5_i3_itr);

  return itr(prev_i1, next_i1,
	     prev_i2, next_i2,
	     prev_i3, next_i3);
}

// (6) ------ Example 6 ------

vtss::expose::TableStatus<vtss::expose::ParamKey<demo_ex6_index_t>,
                          vtss::expose::ParamVal<demo_ex6_attr_t *>> demo_ex6_status("mutex_ex6_status",
										     VTSS_MODULE_ID_DEMO_SNMP);


mesa_rc demo_ex6_set(demo_ex6_index_t  index,
		     const demo_ex6_attr_t  *const a)
{
  // We will just print out the set values,
  // and skip actually to save the values.
  //
  printf("%s index=%d value=(%d,%d)\n",
	 __FUNCTION__,
	 index,
	 a->attr1_ex6, a->attr2_ex6);

  return VTSS_RC_OK;
}

mesa_rc demo_ex6_get(demo_ex6_index_t  index,
		     demo_ex6_attr_t  *const a)
{
  // Just return i1+i2 in attr1 and i2+i3 in attr2
  a->attr1_ex6 = index;
  a->attr2_ex6 = index*2;

  return VTSS_RC_OK;
}

mesa_rc demo_ex6_itr(const demo_ex6_index_t  *prev_index,
		     demo_ex6_index_t        *next_index)
{
  // -If prev_index is NULL, then return first index in *next_iindex and return VTSS_RC_OK.
  // -If prev_index is not NULL and *prev_i1 is not the last index, then
  //  return the next index in *next_iindex and return VTSS_RC_OK.
  // -If prev_index is not NULL and *prev_index is the last index, then return VTSS_RC_ERROR.

  // We iterate over the numbers 0,...,5
  //
  if (!prev_index)  *next_index=0;
  else if (*prev_index<5) *next_index = *prev_index + 1;
  else return VTSS_RC_ERROR;

  return VTSS_RC_OK;
}

void demo_ex6_generate_trap(int mode, int key, int value)
{
  demo_ex6_attr_t a;
  a.attr1_ex6 = value;

  // Setting the value from the system will generate a SNMP trap.
  // Do that with ICLI commands 'demo trap 1'.
  //
  switch (mode) {
  case 0: /*set*/ demo_ex6_status.set(key, &a); break;
  case 1: /*del*/ demo_ex6_status.del(key); break;
  }
}

bool operator!=(const demo_ex6_attr_t& x, const demo_ex6_attr_t& y)
{
  return x.attr1_ex6!=y.attr1_ex6 || x.attr2_ex6!=y.attr2_ex6;
}



// (7) ------ Example 7 ------

mesa_rc demo_ex7_get(demo_ex7_index_t  i,
		     demo_ex7_attr_t  *const a)
{
  a->attr1_ex7 = i+2;
  a->attr2_ex7 = i*2;
  
  printf("%s i=%d attr1=%d attr2=%d\n", __FUNCTION__, i, a->attr1_ex7, a->attr2_ex7);

  return VTSS_RC_OK;
}

mesa_rc demo_ex7_set(demo_ex7_index_t  i,
		     const demo_ex7_attr_t  *const a)
{
  printf("%s i=%d attr1=%d attr2=%d\n", __FUNCTION__, i, a->attr1_ex7, a->attr2_ex7);
  return VTSS_RC_OK;
}

mesa_rc demo_ex7_add(demo_ex7_index_t  i,
		     const demo_ex7_attr_t  *const a)
{
  printf("%s i=%d attr1=%d attr2=%d\n", __FUNCTION__, i, a->attr1_ex7, a->attr2_ex7);

  return VTSS_RC_OK;
}

mesa_rc demo_ex7_itr(const demo_ex7_index_t  *prev_i,
		     demo_ex7_index_t        *next_i)
{
  mesa_rc rc=VTSS_RC_OK;

  printf("%s ", __FUNCTION__);
  if (prev_i) printf("*prev=%d", *prev_i); else printf("prev=NULL ");
  if (next_i) printf("*next=%d", *next_i); else printf("next=NULL ");

  if (!prev_i)  *next_i=0;
  else if (*prev_i<5) *next_i = *prev_i + 1;
  else rc = VTSS_RC_ERROR;

  if (next_i) printf("*next=%d", *next_i); else printf("next=NULL ");
  printf(" rc=%d\n", rc);

  return rc;
}

mesa_rc demo_ex7_del(demo_ex7_index_t  i)
{
  // Delete row i
  printf("%s index=%d\n", __FUNCTION__, i );
  return VTSS_RC_OK;
}

mesa_rc demo_ex7_def(demo_ex7_index_t *index, demo_ex7_attr_t *value)
{
  printf("%s index=%d\n", __FUNCTION__, *index );

  *index = 1;
  value->attr1_ex7 = 1;
  value->attr2_ex7 = 3;
  return VTSS_RC_OK;
}
