/* === S Y N F I G ========================================================= */
/*!	\file valuenode_join.cpp
**	\brief Implementation of the "Join" valuenode conversion.
**
**	$Id$
**
**	\legal
**	Copyright (c) 2002-2005 Robert B. Quattlebaum Jr., Adrian Bentley
**	Copyright (c) 2008 Chris Moore
**
**	This package is free software; you can redistribute it and/or
**	modify it under the terms of the GNU General Public License as
**	published by the Free Software Foundation; either version 2 of
**	the License, or (at your option) any later version.
**
**	This package is distributed in the hope that it will be useful,
**	but WITHOUT ANY WARRANTY; without even the implied warranty of
**	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
**	General Public License for more details.
**	\endlegal
*/
/* ========================================================================= */

/* === H E A D E R S ======================================================= */

#ifdef USING_PCH
#	include "pch.h"
#else
#ifdef HAVE_CONFIG_H
#	include <config.h>
#endif

#include "valuenode_join.h"
#include "valuenode_const.h"
#include "valuenode_dynamiclist.h"
#include "canvas.h"
#include "general.h"

#endif

/* === U S I N G =========================================================== */

using namespace std;
using namespace etl;
using namespace synfig;

/* === M A C R O S ========================================================= */

/* === G L O B A L S ======================================================= */

/* === P R O C E D U R E S ================================================= */

/* === M E T H O D S ======================================================= */

ValueNode_Join::ValueNode_Join(const ValueBase &value):
	LinkableValueNode(value.get_type())
{
	switch(value.get_type())
	{
	case ValueBase::TYPE_STRING:
	{
		vector<ValueBase> v(1, value.get(String()));

		// "insert item (smart)" inserts before the selected entry, making it hard to append to the end
		// add an extra element at the end to allow the easy insertion of text after the given value's string
		v.push_back("...");

		set_link("strings",ValueNode_DynamicList::create_from(v));
		set_link("before",ValueNode_Const::create(String("")));
		set_link("separator",ValueNode_Const::create(String(" ")));
		set_link("after",ValueNode_Const::create(String("")));
		break;
	}
	default:
		throw Exception::BadType(ValueBase::type_local_name(value.get_type()));
	}
}

LinkableValueNode*
ValueNode_Join::create_new()const
{
	return new ValueNode_Join(get_type());
}

ValueNode_Join*
ValueNode_Join::create(const ValueBase &x)
{
	return new ValueNode_Join(x);
}

ValueNode_Join::~ValueNode_Join()
{
	unlink_all();
}

ValueBase
ValueNode_Join::operator()(Time t)const
{
	if (getenv("SYNFIG_DEBUG_VALUENODE_OPERATORS"))
		printf("%s:%d operator()\n", __FILE__, __LINE__);

	const std::vector<ValueBase> strings((*strings_)(t).get_list());
	const String before((*before_)(t).get(String()));
	const String separator((*separator_)(t).get(String()));
	const String after((*after_)(t).get(String()));

	switch (get_type())
	{
	case ValueBase::TYPE_STRING:
	{
		bool first = true;
		String ret(before);
		for (std::vector<ValueBase>::const_iterator iter = strings.begin(); iter != strings.end(); iter++)
		{
			if (first)
				first = false;
			else
				ret += separator;
			ret += iter->get(String());
		}
		ret += after;
		return ret;
	}
	default:
		break;
	}

	assert(0);
	return ValueBase();
}

String
ValueNode_Join::get_name()const
{
	return "join";
}

String
ValueNode_Join::get_local_name()const
{
	return _("Joined List");
}

bool
ValueNode_Join::set_link_vfunc(int i,ValueNode::Handle value)
{
	assert(i>=0 && i<link_count());

	switch(i)
	{
	case 0: CHECK_TYPE_AND_SET_VALUE(strings_, ValueBase::TYPE_LIST);
	case 1: CHECK_TYPE_AND_SET_VALUE(before_, ValueBase::TYPE_STRING);
	case 2: CHECK_TYPE_AND_SET_VALUE(separator_, ValueBase::TYPE_STRING);
	case 3: CHECK_TYPE_AND_SET_VALUE(after_, ValueBase::TYPE_STRING);
	}
	return false;
}

ValueNode::LooseHandle
ValueNode_Join::get_link_vfunc(int i)const
{
	assert(i>=0 && i<link_count());

	switch(i)
	{
	case 0: return strings_;
	case 1: return before_;
	case 2: return separator_;
	case 3: return after_;
	}

	return 0;
}

int
ValueNode_Join::link_count()const
{
	return 4;
}

String
ValueNode_Join::link_name(int i)const
{
	assert(i>=0 && i<link_count());

	switch(i)
	{
		case 0: return "strings";
		case 1: return "before";
		case 2: return "separator";
		case 3: return "after";
	}
	return String();
}

String
ValueNode_Join::link_local_name(int i)const
{
	assert(i>=0 && i<link_count());

	switch(i)
	{
		case 0: return _("Strings");
		case 1: return _("Before");
		case 2: return _("Separator");
		case 3: return _("After");
	}
	return String();
}

int
ValueNode_Join::get_link_index_from_name(const String &name)const
{
	if (name=="strings") return 0;
	if (name=="before") return 1;
	if (name=="separator") return 2;
	if (name=="after") return 3;

	throw Exception::BadLinkName(name);
}

bool
ValueNode_Join::check_type(ValueBase::Type type)
{
	return
		type==ValueBase::TYPE_STRING;
}
