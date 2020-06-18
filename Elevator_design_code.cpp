#include<bits/stdc++.h>
using namespace std;

// function to check if there is request from current floor to enter or not
void check_start_request(int &current_floor,int &start_floor,unordered_map<int,vector<int>>&floor_start_request,set<int>&processing,set<int>&completed,int &current_time,bool &start)
{
if(current_floor!=start_floor&&floor_start_request.find(current_floor)!=floor_start_request.end())
        {
          vector<int>temp=floor_start_request[current_floor];
          for(int i=0;i<temp.size();i++)
          {
            if(processing.find(temp[i])==processing.end()&&completed.find(temp[i])==completed.end()&&temp[i]<=current_time)
            {
              start=true;
              processing.insert(temp[i]);
            }
          }
        }

}


// function to check if there is any request to drop at this floor 
void check_end_request(int &current_floor,int &target_floor,unordered_map<int,vector<int>>&floor_end_request,set<int>&processing,set<int>&completed,bool &end)
{
if(current_floor!=target_floor&&floor_end_request.find(current_floor)!=floor_end_request.end())
        {
          vector<int>temp=floor_end_request[current_floor];
          for(int i=0;i<temp.size();i++)
          {

              if(processing.find(temp[i])!=processing.end())
              {
                end=true;
                completed.insert(temp[i]);
                processing.erase(temp[i]);
              }


          }
      }
}



int main()
{
  // making a map to store request which start from a particular floor
  unordered_map<int,vector<int>>floor_start_request;

  // making map to store request end at which floor
  unordered_map<int,vector<int>>floor_end_request;

// represents request in queue
  set<int>processing;

  // represents request completed
  set<int>completed;

// stores request with respect to time
  unordered_map<int,pair<int,int>>request;

//put the request
  request[2]={3,4};
  request[4]={5,6};
  request[19]={7,6};

//filling floor_start_request map
  floor_start_request[3].push_back(2);
  floor_start_request[5].push_back(4);
  floor_start_request[7].push_back(19);

// filling floor_end_request map
  floor_end_request[4].push_back(2);
  floor_end_request[6].push_back(4);
  floor_end_request[6].push_back(19);



// queue to store time of requests
  queue<int>time;
  time.push(2);
  time.push(4);
  time.push(19);

// represents current floor
  int current_floor=0;
  // represents current time
  int current_time=0;

  while(time.size()!=0)
  {
    // time at which request has been made is represented by request_time
      int request_time=time.front();
      time.pop();
      while(current_time<request_time)
      {
        cout<<"Staying still at "<<current_floor;
        cout<<"       "<<current_time<<" to "<<current_time+1<<endl;
        current_time++;
      }
      pair<int,int>floors=request[request_time];
      int start_floor=floors.first;
      int target_floor=floors.second;


// if that request time is in completed set it means that is already done
      if(completed.find(request_time)!=completed.end())
      {
        continue;
      }
      bool inprocess=false;


    // if that request time is in processing set means person who made the request has entered the lift but request is not completed yet.
      if(processing.find(request_time)!=processing.end())
      {
        inprocess=true;
      }


  // if it is not in processing state then we need to got to start floor else only move towards the target floor
      if(inprocess==false)
      {
      if(current_floor<start_floor)
      {
        //moving towards the start_floor from current floor if current_floor is less than start_floor
      while(current_floor<start_floor)
      {
        cout<<"Moving from "<<current_floor<<" to "<<current_floor+1;
        cout<<"       "<<current_time<<" to "<<current_time+1<<endl;
        current_floor++;
        current_time++;

        bool start=false;
        bool end=false;

// checking if there is request from this floor to enter or not
        check_start_request(current_floor,start_floor,floor_start_request,processing,completed,current_time,start);


// checking if there is any request to drop at this floor 
        check_end_request(current_floor,target_floor,floor_end_request,processing,completed,end);

// if any of above is true then we will open the gate and close it
        if(start||end)
        {
          cout<<"Opening door at "<<current_floor<<" floor";
          cout<<"       "<<current_time<<" to "<<current_time+1<<endl;
          current_time++;
          cout<<"Closing door at "<<current_floor<<" floor";
          cout<<"       "<<current_time<<" to "<<current_time+1<<endl;
          current_time++;
        }


      }
      }
      if(current_floor>start_floor)
      {
        //moving towards the start floor downwards if current floor is greater than start_floor
        while(current_floor>start_floor)
        {
          cout<<"Moving from "<<current_floor<<" to "<<current_floor-1;
          cout<<"       "<<current_time<<" to "<<current_time+1<<endl;
          current_floor--;
          current_time++;

          bool start=false;
          bool end=false;

// checking if there is request from this floor to enter or not
         check_start_request(current_floor,start_floor,floor_start_request,processing,completed,current_time,start);


// checking if there is any request to drop at this floor
        check_end_request(current_floor,target_floor,floor_end_request,processing,completed,end);
// if any of above is true then we will open the gate and close at this floor
      if(start||end)
      {
        cout<<"Opening door at "<<current_floor<<" floor";
          cout<<"       "<<current_time<<" to "<<current_time+1<<endl;
          current_time++;
          cout<<"Closing door at "<<current_floor<<" floor";
          cout<<"       "<<current_time<<" to "<<current_time+1<<endl;
          current_time++;
      }


        }
      }


//at this time my current_floor is equal to start_floor so i will open the gate for the person to move and close the door



      processing.insert(request_time);

      if(floor_start_request.find(current_floor)!=floor_start_request.end())
        {
          vector<int>temp=floor_start_request[current_floor];
          for(int i=0;i<temp.size();i++)
          {
            if(processing.find(temp[i])==processing.end()&&completed.find(temp[i])==completed.end()&&temp[i]<=current_time)
            {
              processing.insert(temp[i]);
            }
          }
        }


      if(floor_end_request.find(current_floor)!=floor_end_request.end())
        {
          vector<int>temp=floor_end_request[current_floor];
          for(int i=0;i<temp.size();i++)
          {

              if(processing.find(temp[i])!=processing.end())
              {
                completed.insert(temp[i]);
                processing.erase(temp[i]);
              }


          }
      }


      cout<<"Opening door at "<<current_floor<<" floor";
      cout<<"       "<<current_time<<" to "<<current_time+1<<endl;
      current_time++;
      cout<<"Closing door at "<<current_floor<<" floor";
      cout<<"       "<<current_time<<" to "<<current_time+1<<endl;
      current_time++;
      }









      if(current_floor<target_floor)
      {
        //moving towards the target floor from current floor if current floor is less than taeget floor
      while(current_floor<target_floor)
      {
        cout<<"Moving from "<<current_floor<<" to "<<current_floor+1;
        cout<<"       "<<current_time<<" to "<<current_time+1<<endl;
        current_floor++;
        current_time++;

        bool start=false;
        bool end=false;
// checking if there is request from this floor to enter or not
        check_start_request(current_floor,target_floor,floor_start_request,processing,completed,current_time,start);

// checking if there is any request to drop at this floor
        check_end_request(current_floor,target_floor,floor_end_request,processing,completed,end);

// if any of above is true then we will open the gate and close at this floor
        if(start||end)
        {
           cout<<"Opening door at "<<current_floor<<" floor";
          cout<<"       "<<current_time<<" to "<<current_time+1<<endl;
          current_time++;
          cout<<"Closing door at "<<current_floor<<" floor";
          cout<<"       "<<current_time<<" to "<<current_time+1<<endl;
          current_time++;
        }
      }
      }

      if(current_floor>target_floor)
      {
        //moving towards the target_floor from current floor if current floor is more than target floor
        while(current_floor>target_floor)
        {
          cout<<"Moving from "<<current_floor<<" to "<<current_floor-1;
          cout<<"       "<<current_time<<" to "<<current_time+1<<endl;
        current_floor--;
        current_time++;

        bool start=false;
        bool end=false;

// checking if there is request from this floor to enter or not
         check_start_request(current_floor,target_floor,floor_start_request,processing,completed,current_time,start);

// checking if there is any request to drop at this floor

        check_end_request(current_floor,target_floor,floor_end_request,processing,completed,end);
        // if any of above is true then we will open the gate and close at this floor
        if(start||end)
        {
             cout<<"Opening door at "<<current_floor<<" floor";
          cout<<"       "<<current_time<<" to "<<current_time+1<<endl;
          current_time++;
          cout<<"Closing door at "<<current_floor<<" floor";
          cout<<"       "<<current_time<<" to "<<current_time+1<<endl;
          current_time++;
        }
        }
      }


// at this time our current_floor is equal to target floor for this particular request which we are serving
      if(processing.find(request_time)!=processing.end())
      {
        processing.erase(request_time);
      }
      completed.insert(request_time);

      if(floor_start_request.find(current_floor)!=floor_start_request.end())
        {
          vector<int>temp=floor_start_request[current_floor];
          for(int i=0;i<temp.size();i++)
          {
            if(processing.find(temp[i])==processing.end()&&completed.find(temp[i])==completed.end()&&temp[i]<=current_time)
            {
              processing.insert(temp[i]);
            }
          }
        }


      if(floor_end_request.find(current_floor)!=floor_end_request.end())
        {
          vector<int>temp=floor_end_request[current_floor];
          for(int i=0;i<temp.size();i++)
          {

              if(processing.find(temp[i])!=processing.end())
              {
                completed.insert(temp[i]);
                processing.erase(temp[i]);
              }


          }
      }


      cout<<"Opening door at "<<current_floor<<" floor";
      cout<<"       "<<current_time<<" to "<<current_time+1<<endl;
      current_time++;
      cout<<"Closing door at "<<current_floor<<" floor";
      cout<<"       "<<current_time<<" to "<<current_time+1<<endl;
      current_time++;
  }

  



}