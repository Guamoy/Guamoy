BEGIN{
	FS = ",";
	numCalls = 0;
	timeStamp;
	clockTime;
}
{
	timeStamp = substr($2,2,10); #this program will break by the year 10000
	clockTime = substr($2,13,8); #assumes input is constant in formatting... lol
	
	if (timeStamp in datesFirst){
		split(datesFirst[timeStamp],a,",");
		if (substr(a[2],13,8) > clockTime) 
			datesFirst[timeStamp] = $0;
	}
	else
		datesFirst[timeStamp] = $0;
	
	if (timeStamp in datesLast){
		split(datesLast[timeStamp],b,",");
		if (substr(b[2],13,8) < clockTime)
			datesLast[timeStamp] = $0;
	}
	else
		datesLast[timeStamp] = $0;

	if ($3 in probType)
		probType[$3] += 1;
	else
		probType[$3] = 1;
	
	if ($5 in division)
		division[$5] += 1;
	else
		division[$5] = 1;

	numCalls++;

}
END{

	print "Total calls =",numCalls,"\n";
	for (key in datesFirst)
	{
		print "Date: " key;
		print "\tFirst Call: " datesFirst[key];
		print "\tLast Call: " datesLast[key]"\n";
	}
	print "Per-problem totals:";
	
	for (key in probType)
		print "\t",key":",probType[key]; 
	print "\nPer-Division totals:";

	for (key in division)
		print "\t",key":",division[key];

}
