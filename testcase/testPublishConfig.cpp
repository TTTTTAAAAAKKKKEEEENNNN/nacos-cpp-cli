#include <iostream>
#include <stdlib.h>
#include "NacosConfigService.h"
#include "PropertyKeyConst.h"
#include "Debug.h"

using namespace std;

void testPublishConfig()
{
	cout << "in function testPublishConfig" << endl;
	Properties props;
	props[PropertyKeyConst::SERVER_ADDR] = "127.0.0.1:8848";
	NacosConfigService *n = new NacosConfigService(props);
	bool bSucc;
	for (int i = 5; i < 50; i++)
	{
		char key_s[200];
		char val_s[200];
		sprintf(key_s, "Key%d", i);
		sprintf(val_s, "v__%d", i);

		try
		{
			bSucc = n->publishConfig(key_s, NULLSTR, val_s);
		}
		catch (NacosException e)
		{
			cout <<
			"Request failed with curl code:"<<e.errorcode() << endl <<
			"Reason:" << e.what() << endl;
		}
		cout << "Publishing Key:" << key_s << " with value:" << val_s << " result:" << bSucc << endl;
	}

	delete n;
	n = NULL;
}