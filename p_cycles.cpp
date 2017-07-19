#include<iostream>
#include<stdio.h>
#include<fstream>
#include<cmath>
using namespace std;
struct shield{
	int l_leg, r_leg, mark, flag, slopel, sloper, last_set;
};

int main(){

    ifstream readl;
    ifstream readr;
    ofstream write;
    ofstream remark;
    readl.open("pinputl.in");
    readr.open("pinputr.in");
    write.open("poutput4.out");
    remark.open("REMARKS.out");
    ////////////////////////////////////////// STRUCTURE ARRAY ///////////////////////////
    struct shield psr[146],temp[146];
    
    
    ////////////////////////////////////////// MY VARIABLES /////////////////////////////
    int count[146],i,time=0,min=0;
    string s,sarr[150];
    
    
    for(i=0;i<146;i++){
    		count[i]=0;
    }
    readl>>s;
    readr>>s;
    for(i=0;i<146;i++){
	    	readl>>temp[i].l_leg;
	    	readr>>temp[i].r_leg;
	    	temp[i].mark=0;
	    	temp[i].flag=0;
	    	temp[i].slopel=0;
	    	temp[i].sloper=0;
	    	temp[i].last_set=0;
    }
    time+=10;
    
    while(!readl.eof()){
    		readl>>s;
    		readr>>s;
    		time+=10;
    		if(time%60==0){
    			time=0;
    			min = min+1;
    		}
    		for(i=0;i<146;i++){
    			readl>>psr[i].l_leg;
    			readr>>psr[i].r_leg;
    			psr[i].mark=0;
    			psr[i].flag=0;
    			
    		////////////////////////  CORRECTION FOR ONE LEG SENSOR  ///////////////////////////////	
    			/*if(psr[i].r_leg==-1 && temp[i].r_leg==-1 && psr[i].l_leg>100){
    				psr[i].mark=2;
    				psr[i].sloper = 0;
    			}
    			else{
    				if(psr[i].l_leg==-1 && temp[i].l_leg==-1 && psr[i].r_leg>100){
    					psr[i].mark=1;
    					psr[i].slopel = 0;
    				}
    			}
    			
    			if(psr[i].r_leg>0 && temp[i].r_leg==-1 && psr[i].l_leg>100){
    				cout<<i<<endl;
    				psr[i].mark=4;
    				psr[i].sloper=0;
    			}
    			else{
    				if(psr[i].l_leg>0 && temp[i].l_leg==-1 && psr[i].r_leg>100){
    					cout<<i<<endl;
    					psr[i].mark=3;
    					psr[i].slopel=0;
    				}
    			}*/
    			
    		////////////////////////  CORRECTION FOR ONE LEG SENSOR  ///////////////////////////////	
    		
    			if(psr[i].r_leg==-1 && psr[i].l_leg>0){
    				psr[i].mark=2;
    				psr[i].sloper = 0;
    				remark<<s<<"	"<<"DAY 1"<<"	"<<"right leg sensor of shield "<<i+1<<" not working"<<endl;
    			}
    			else{
    				if(psr[i].l_leg==-1 && psr[i].r_leg>0){
    					psr[i].mark=1;
    					psr[i].slopel=0;
    					remark<<s<<"	"<<"DAY 1"<<"	"<<"left  leg sensor of shield "<<i+1<<" not working"<<endl;
    				}
    			}
    			
    		////////////////////////////////  NEGLECTING VALUES WITH BOTH SENSOR ERROR ////////////////////////////	
    			if(psr[i].l_leg==-1 && psr[i].r_leg==-1){
    				psr[i].mark=-1;
    				psr[i].flag=1;
    				psr[i].slopel = -1;
    				psr[i].sloper = -1;
    				psr[i].last_set=-1;
    				count[i]=-1;
    			}
    			
    		//////////////////////////  FOR CORRECT SENSORS //////////////////////////////////
    			else{
    				if(psr[i].mark==0){
    					psr[i].slopel = ((psr[i].l_leg) - (temp[i].l_leg))/10; 
    					psr[i].sloper = ((psr[i].r_leg) - (temp[i].r_leg))/10;
    				}
    				else{
    					if(psr[i].mark==2 || psr[i].mark==4){
    						psr[i].slopel = ((psr[i].l_leg) - (temp[i].l_leg))/10;
    						psr[i].sloper = psr[i].slopel;
 					}
 					if(psr[i].mark==1 || psr[i].mark==3){
 						psr[i].sloper = ((psr[i].r_leg) - (temp[i].r_leg))/10;
 						psr[i].slopel = psr[i].sloper;
 					}
 					   				
    				}
    					
    				
    				if((psr[i].slopel<=-10 || psr[i].sloper<=-10)){
    					if(psr[i].last_set < (min-60) || psr[i].last_set==0){
    						if(i==56){
    							cout<<s<<"  "<<min<<"   "<<psr[i].last_set<<"   "<<psr[i].slopel<<"   "<<psr[i].sloper<<endl;
    						}
    						count[i]++;
    						psr[i].last_set = min;
    					}
    				}
    			}
    			temp[i].l_leg = psr[i].l_leg;
    			temp[i].r_leg = psr[i].r_leg;
    		}
    }
    for(i=0;i<146;i++){
    		if(count[i]==-1 && i!=0){
    			write<<i+1<<" --------->"<<count[i-1]<<endl;
    		}
    		else{
    			write<<i+1<<" --------->"<<count[i]<<endl;
    		}
    }
    readl.close();
    readr.close();
    write.close();
    
}
    
    //cout<<s<<" "<<templ<<" "<<tempr;
   /* while(!read.eof()){
        read.ignore();
        read>>s;	
        read>>pl>>pr;
        slope_l = (pl-templ)/10;
        slope_r = (pr-tempr)/10;
        //cout<<templ<<" "<<pl<<" "<<tempr<<" "<<pr<<" "<<slope_l<<" "<<slope_r<<endl;
        if(slope_l<-30 && slope_r<-30){
            countt++;
        }
        templ = pl;
        tempr = pr;
    }
    //cout<<pl<<" "<<pr<<endl;
    write<<countt;
    read.close();
    write.close();
}*/
