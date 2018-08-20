/*
 * RandomAccessBag.cpp
 *
 *  Created on: Aug 15, 2018
 *      Author: sujiwo
 */

#include <rosbag/query.h>
#include "datasets/RandomAccessBag.h"




/*
 * Only allows one single topic
 */
RandomAccessBag::RandomAccessBag
	(rosbag::Bag const &bag, const std::string &topic,
	double startTimeOffsetSecond, double mappingDurationSecond):

	rosbag::View::View(),
	bagstore(const_cast<rosbag::Bag&>(bag))

{
	addQuery(bag, rosbag::TopicQuery(topic));

	conn = getConnections()[0];
	createCache();
}


RandomAccessBag::~RandomAccessBag()
{
}


void
RandomAccessBag::createCache()
{
	iterator it = begin();
	size_t sz = size();
	msgPtr.resize(sz);

	for (uint32_t p=0; p<sz; p++) {
		rosbag::MessageInstance &m = *it;
		rosbag::IndexEntry const ie = access_private::index_entry_(m);
		msgPtr.at(p) = ie;
		++it;
	}
}
