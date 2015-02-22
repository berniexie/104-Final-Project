void MainWin::PageRank(Set<WebPage*> &tee)
{

	set<WebPage *>::iterator it = tee.begin();
	//cout<<"tee size is: "<<tee.size()<<endl;
	double teedummy=tee.size();
	while(it!=tee.end())//set all nodes' initial probability to 1/(size of graph)
	{

		(*it)->pr=(1/teedummy);
		++it;
	}

	for(int i=0; i<30; i++)
	{
		double sinksum=0;

		for(set<WebPage*>::iterator sinkit=tee.begin(); sinkit!=tee.end(); ++sinkit) //calculating sum of probability you end on a sink
		{
			//cout<<"In tee set :"<<(*sinkit)->file<<endl;
			Set<string> sinkString = (*sinkit)->allOutgoingLinks();//converting string to webpage
			//cout<<(**sinkit).file<<" size of outgoing links is: "<<(*sinkit)->allOutgoingLinks().size()<<endl;
			Set<WebPage*> sinkWebpage;
			for (set<string>::iterator sinker=sinkString.begin(); sinker!=sinkString.end(); ++sinker)
			{
				//cout<<"Inserting a value"<<endl;
				sinkWebpage.insert(&(nameFiles.at(*sinker)));
			}
			//cout<<"sinkwebpage size is :"<<sinkWebpage.size()<<endl;
			Set<string> teeString;
			for (set<WebPage*>::iterator dummy=tee.begin(); dummy!=tee.end(); ++dummy)
			{
				teeString.insert((*dummy)->file);
			}
			Set<string> sinkSet = teeString.setIntersection(sinkString);
			//Set<WebPage*> sinkSet = tee.setIntersection(sinkWebpage);
			//cout<<"sinkset size is: "<<sinkSet.size()<<endl;
			if(sinkSet.size()==0)
			{
				sinksum += (*sinkit)->pr;
			}
		}

		sinksum = sinksum / teedummy; //spreading sink probability over all nodes

		for(it=tee.begin(); it!=tee.end(); ++it)
		{
			//cout<<"OVERALL FILE IS: "<<(*it)->file<<endl;
			Set<string>   stringFeeders = (**it).allIncomingLinks();//converting string to webpage
			//tee.setIntersection(**it)->allIncomingLinks());
			Set<string>   stringOuts  = (**it).allOutgoingLinks(); 
			//tee.setIntersection((**it)->allOutgoingLinks());
			Set<WebPage*> webpageFeeders;
			Set<WebPage*> webpageOuts;
			Set<string> teeString;
			for (set<WebPage*>::iterator dummy=tee.begin(); dummy!=tee.end(); ++dummy)
			{
				teeString.insert((*dummy)->file);
			}
			Set<string> intersectionFeeder=teeString.setIntersection(stringFeeders);
			Set<WebPage*> feeders;
			for (set<string>::iterator it2=intersectionFeeder.begin(); it2!=intersectionFeeder.end(); ++it2)
			{
				feeders.insert(&(nameFiles.at(*it2)));
			}
			//cout<<"feeders size is : "<<feeders.size()<<endl;
			//cout<<"feeder first element is :"<<(*(feeders.begin()))->file<<endl;
			Set<string> outs= teeString.setIntersection(stringOuts);


			double scoresum = 0;

			if (feeders.size()==0)
			{
				scoresum = 0;
				(*it)->prnew= (.15/teedummy) + (.85 * (scoresum+sinksum));
			}



			else 
			{

				for(set<WebPage*>::iterator itagain=feeders.begin(); itagain!=feeders.end(); ++itagain)
				{
					Set<string> spreadSet=(*itagain)->allOutgoingLinks();//converting string to webpage
					Set<WebPage*> spreadPage;
					Set<string> teeString;
					for (set<WebPage*>::iterator dummy=tee.begin(); dummy!=tee.end(); ++dummy)
					{
						teeString.insert((*dummy)->file);
					}
					/*for(set<string>::iterator it4=spreadSet.begin(); it4!=spreadSet.end(); ++it4)
					{
						spreadPage.insert(&(nameFiles.at(*it4)));
					}*/
					//Set<string> OutgoingNames =
					Set<string> trash = teeString.setIntersection(spreadSet);
					double spread = trash.size();
					cout<<(*itagain)->file<<endl;
					for(set<WebPage*>::iterator it5=tee.begin(); it5!=tee.end(); ++it5)
					{
						if ((*it5)->file==(*itagain)->file)
						{
							scoresum+= ((*it5)->pr)/spread;
						}
					}
					//scoresum += ((*itagain)->pr)/spread;//score is incoming link's probably spread over all its relevant outgoing links
				}
			//	cout<<"scoresume: "<<scoresum<<"sinksum: "<<sinksum<<endl;

				(*it)->prnew= (.15/teedummy) + (.85 * (scoresum+sinksum));

			}


		}

		for(Set<WebPage*>::iterator resetit=tee.begin(); resetit!=tee.end(); ++resetit)
		{
			(*resetit)->pr=(*resetit)->prnew;
		}

	}


}
