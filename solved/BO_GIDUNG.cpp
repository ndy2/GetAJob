#include <string>
#include <vector>
#include <iostream>
#include <utility>
#include <algorithm>
#define MAX_FRAME_SIZE 101
#define BO_GIDUNG 2
#define BO 1
#define GIDUNG 0
#define EMPTY -1
#define MAKE 1
#define REMOVE 0
using namespace std;

//initialize 쳐봄
vector<int> map_row(MAX_FRAME_SIZE,EMPTY);
vector<vector<int>> map(MAX_FRAME_SIZE, map_row);


bool sortFunc(vector<int>& a, vector<int>&b)
{
     return b[0]>a[0]?true:
          (b[0]<a[0]?false:
           (b[1]>a[1])?true:
            (b[1]<a[1]?false:
            (b[2]>a[2])));
}

bool validation_test(vector<int> info, int n, bool type_frame, bool type_job)
{
    //job validation
    if(type_job == MAKE)
    {
        if(map[info[0]][info[1]]== type_frame) return false;
    }
    else if(type_job == REMOVE)
    {
        if(map[info[0]][info[1]]== EMPTY) return false;
    }
    return true;
}

bool range_test(vector<int> info, int n, bool type_frame, bool type_job)
{
    //range test
    if(type_frame == BO)
    {
        if(info[0]>= n || info[1] >n || info[1]<=0 || info[0]<0) return false;
    }
    else if(type_frame == GIDUNG)
    {
        if(info[0]> n || info[1] >=n || info[0]<0 || info[1]<0) return false;
    }
    return true;
}

bool logic_test(vector<int> info, int n, bool type_frame, bool type_job)
{
    //MAKE - true(success) oriented
    if(type_job == MAKE)
    {
        if(type_frame == GIDUNG)
            {
                //바닥위에 설치 success
                if(info[1] == 0) return true;
                //다른 기둥 위에 설치 success
                else if((info[1]!=0)     && ( map[info[0]][info[1]-1] == GIDUNG || map[info[0]][info[1]-1] == BO_GIDUNG)) return true;
                //왼쪽에 보가 있는 경우 success
                else if((info[0]!=0)     && ( map[info[0]-1][info[1]] == BO     || map[info[0]-1][info[1]] == BO_GIDUNG)) return true;
                //오른쪽에 보가 있는 경우 success
                else if( map[info[0]][info[1]] == BO     || map[info[0]][info[1]] == BO_GIDUNG) return true;
                
            }
        else if(type_frame == BO)
        {
            //왼쪽 끝에 기둥이 있는 경우 success
            if     ((info[1]!=0)&&                  ( map[info[0]][info[1]-1]   ==  GIDUNG || map[info[0]][info[1]-1]  == BO_GIDUNG)) return true;
            //오른쪽 끝에 기둥이 있는 경우 success
            else if((info[0]!=n)&& (info[1]!=0)&&(map[info[0]+1][info[1]-1] == GIDUNG || map[info[0]+1][info[1]-1] == BO_GIDUNG)) return true;
            //양쪽 끝에 보가 있는 경우 success
            else if( (info[0]!=0) && (info[0]!=n-1)&&
                (map[info[0]-1][info[1]]     == BO    || map[info[0]-1][info[1]]   == BO_GIDUNG ) 
                &&(map[info[0]+1][info[1]]   == BO    || map[info[0]+1][info[1]]   == BO_GIDUNG )) return true;
        }
        else{
            return false;
        }

    }
    else if(type_job == REMOVE)
    {
         bool ret = true; 
         //REMOVE - false(fail) oriented
            if(type_frame == GIDUNG)
            {
                //logic_test를 위해 잠깐 remove position의 gidung frame을 제거함
                if(map[info[0]][info[1]] == GIDUNG)
                            map[info[0]][info[1]] = EMPTY;
                else if(map[info[0]][info[1]] == BO_GIDUNG)
                    map[info[0]][info[1]] = BO;

                //윗 기둥이 logic_test 를 통과 하지 못하는 경우 fail
                vector<int> info_upper_gidung = info;
                info_upper_gidung[1] +=1;
                if(range_test(info_upper_gidung,n,GIDUNG,MAKE) && (map[info_upper_gidung[0]][info_upper_gidung[1]] == GIDUNG || map[info_upper_gidung[0]][info_upper_gidung[1]] == BO_GIDUNG))
                    if(!logic_test(info_upper_gidung, n, GIDUNG, MAKE))
                        ret = false;
                //왼쪽 보가 logic_test 를 통과 하지 못하는 경우 fail
                vector<int> info_left_bo = info;
                info_left_bo[0] -=1;
                info_left_bo[1] +=1;
                if(ret&&range_test(info_left_bo,n,BO,MAKE) &&(map[info_left_bo[0]][info_left_bo[1]] == BO || map[info_left_bo[0]][info_left_bo[1]] == BO_GIDUNG))
                    if(!logic_test(info_left_bo, n, BO, MAKE))
                        ret = false;
                
                //오른쪽 보가 logic_test 를 통과 하지 못하는 경우 fail
                vector<int> info_right_bo = info;
                info_right_bo[1] +=1;
                if(ret&&range_test(info_right_bo,n,BO,MAKE) && (map[info_right_bo[0]][info_right_bo[1]] == BO || map[info_right_bo[0]][info_right_bo[1]] == BO_GIDUNG))
                    if(!logic_test(info_right_bo, n, BO, MAKE))
                        ret = false;
                
                //remove position의 gidung frame 복구
                if(map[info[0]][info[1]] == EMPTY)
                            map[info[0]][info[1]] = GIDUNG;
                else if(map[info[0]][info[1]] == BO)
                    map[info[0]][info[1]] = BO_GIDUNG;

                return ret;
            }
            else if(type_frame == BO)
            {
                //logic_test를 위해 잠깐 remove position의 bo frame을 제거함
                if(map[info[0]][info[1]] == BO)
                            map[info[0]][info[1]] = EMPTY;
                else if(map[info[0]][info[1]] == BO_GIDUNG)
                    map[info[0]][info[1]] = GIDUNG;

                //오른쪽 보가 logic_test 를 통과 하지 못하는 경우 fail
                vector<int> info_right_bo = info;
                info_right_bo[0] +=1;
                if(range_test(info_right_bo,n,BO,MAKE) && (map[info_right_bo[0]][info_right_bo[1]] == BO || map[info_right_bo[0]][info_right_bo[1]] == BO_GIDUNG))
                    if(!logic_test(info_right_bo, n, BO, MAKE))
                        ret = false;

                //왼쪽 보가 logic_test 를 통과 하지 못하는 경우 fail   
                vector<int> info_left_bo = info;
                info_left_bo[0] -=1;
                if(ret&&range_test(info_left_bo,n,BO,MAKE) && (map[info_left_bo[0]][info_left_bo[1]] == BO || map[info_left_bo[0]][info_left_bo[1]] == BO_GIDUNG))
                    if(!logic_test(info_left_bo, n, BO, MAKE))
                        ret = false;

                //오른쪽 기둥이 logic_test 를 통과 하지 못하는 경우 fail
                vector<int> info_right_gidung = info;
                info_right_gidung[0] +=1;
                if(ret&&range_test(info_right_gidung,n,GIDUNG,MAKE) && (map[info_right_gidung[0]][info_right_gidung[1]] == GIDUNG || map[info_right_gidung[0]][info_right_gidung[1]] == BO_GIDUNG))
                    if(!logic_test(info_right_gidung, n, GIDUNG, MAKE))
                        ret = false;

                //왼쪽 기둥이 logic_test 를 통과 하지 못하는 경우 fail
                vector<int> info_left_gidung = info;
                if(ret&&range_test(info_left_gidung,n,GIDUNG,MAKE) && (map[info_left_gidung[0]][info_left_gidung[1]] == GIDUNG || map[info_left_gidung[0]][info_left_gidung[1]] == BO_GIDUNG))
                    if(!logic_test(info_left_gidung, n, GIDUNG, MAKE))
                        ret = false;
                //remove position의 bo frame 복구
                if(map[info[0]][info[1]] == EMPTY)
                            map[info[0]][info[1]] = BO;
                else if(map[info[0]][info[1]] == GIDUNG)
                    map[info[0]][info[1]] = BO_GIDUNG;

                return ret;
            }
    }
   

    //dummy return
    return type_job == MAKE ? false : true;
}


bool make_gidung(vector<int> info, int n)
{
    if(!range_test(info,n,GIDUNG,MAKE))
        return false;
    if(!validation_test(info,n,GIDUNG,MAKE))
        return false;
    if(!logic_test(info,n,GIDUNG,MAKE))
        return false;
    return true;
}

bool make_bo(vector<int> info, int n)
{
    if(!range_test(info,n,BO,MAKE))
        return false;
    if(!validation_test(info,n,BO,MAKE))
        return false;
    if(!logic_test(info,n,BO,MAKE))
        return false;
    return true;
}
bool remove_gidung(vector<int> info, int n)
{
    if(!range_test(info,n,GIDUNG,REMOVE))
        return false;
    if(!validation_test(info,n,GIDUNG,REMOVE))
        return false;
    if(!logic_test(info,n,GIDUNG,REMOVE))
        return false;
    return true;
}

bool remove_bo(vector<int> info, int n)
{
    if(!range_test(info,n,BO,REMOVE))
        return false;
    if(!validation_test(info,n,BO,REMOVE))
        return false;
    if(!logic_test(info,n,BO,REMOVE))
        return false;
    return true;
}

vector<vector<int>> solution(int n, vector<vector<int>> build_frame) {
    vector<vector<int>> answer;
    int i = 1; 
    for (auto frame : build_frame)
    {
        bool complete_process;
        vector<int> info = {frame[0],frame[1]};
        int proc_type = 2*frame[2] + 1* frame[3];
        switch(proc_type)
        {
            case 0 : {
                complete_process = remove_gidung(info ,n);
                break;
            }
            case 1 : {
                complete_process = make_gidung(info ,n);
                break;
            }
            case 2 : {
                complete_process = remove_bo(info ,n);
                break;
            }
            case 3 : {
                complete_process = make_bo(info ,n);
                break;
            }
        }
        cout<<i<<"th work - complete_process : "<< complete_process<<endl;
        i++;

        if (complete_process)
        {
        //global map logic
        // case 0 : remove gidung
        // case 1 : make   gidung
        // case 2 : remove bo
        // case 3 : make   bo
        switch(proc_type)
                {
                    case 0 : {
                        if(map[info[0]][info[1]] == GIDUNG)
                            map[info[0]][info[1]] = EMPTY;
                        else if(map[info[0]][info[1]] == BO_GIDUNG)
                            map[info[0]][info[1]] = BO;
                        break;
                    }
                    case 1 : {
                        if(map[info[0]][info[1]] == EMPTY)
                            map[info[0]][info[1]] = GIDUNG;
                        else if(map[info[0]][info[1]] == BO)
                            map[info[0]][info[1]] = BO_GIDUNG;
                        break;
                    }
                    case 2 : {
                        if(map[info[0]][info[1]] == BO)
                            map[info[0]][info[1]] = EMPTY;
                        else if(map[info[0]][info[1]] == BO_GIDUNG)
                            map[info[0]][info[1]] = GIDUNG;
                        break;
                    }
                    case 3 : {
                        if(map[info[0]][info[1]] == EMPTY)
                            map[info[0]][info[1]] = BO;
                        else if(map[info[0]][info[1]] == GIDUNG)
                            map[info[0]][info[1]] = BO_GIDUNG;
                        break;
                    }
                }
        //answer logic
        // case 0 : remove gidung
        // case 1 : make   gidung
        // case 2 : remove bo
        // case 3 : make   gidung
        switch(proc_type)
                {
                    case 0 : {
                        info.push_back(GIDUNG);
                        //erase-remove idiom 쳐봄
                        answer.erase(remove(answer.begin(), answer.end(), info), answer.end());
                        break;
                    }
                    case 1 : {
                        info.push_back(GIDUNG);
                        answer.push_back(info);
                        break;
                    }
                    case 2 : {
                        info.push_back(BO);
                        //erase-remove idiom 쳐봄
                        answer.erase(remove(answer.begin(), answer.end(), info), answer.end());
                        break;
                    }
                    case 3 : {
                        info.push_back(BO);
                        answer.push_back(info);
                        break;
                    }
                }
        
        }
    }

    sort(answer.begin(),answer.end(),sortFunc);
    return answer;
}
int main()
{
    // #define BO 1
    // #define GIDUNG 0
    int n = 5;
    vector<vector<int>> build_frame1 = {{1,0,0,1},{1,1,1,1}, {2,1,0,1}, {2,2,1,1},
                                        {5,0,0,1}, {5,1,0,1}, {4,2,1,1}, {3,2,1,1}};

    vector<vector<int>> build_frame2 = {{0,0,0,1},{2,0,0,1}, {4,0,0,1}, {0,1,1,1},
                                        {1,1,1,1},{2,1,1,1}, {3,1,1,1}, {2,0,0,0},
                                        {1,1,1,0}, {2,2,0,1}};
    vector<vector<int>> build_frame3 = {{0,0,0,1},{0,1,1,1},{0,0,0,0},{3,0,0,1},{2,1,1,1},{1,1,1,1}};
    vector<vector<int>> build_frame4 = {{0,0,0,1},{0,1,1,1},{1,1,1,1},{2,1,1,1},{3,0,0,1}};
    vector<vector<int>> build_frame5 = {{0,0,0,1},{0,1,1,1},{1,1,1,1},{2,1,1,1},{3,0,0,1}};
    vector<vector<int>> build_frame6 = {{0,0,0,1},{0,1,1,1},{0,1,0,1},{0,2,1,1},{0,2,0,1},{0,3,1,1},{0,3,0,1}};
    vector<vector<int>> build_frame7 = {{0,0,0,1},{0,1,1,1},{0,1,0,1},{0,2,1,1},{0,2,0,1},{0,3,1,1},{0,3,0,1},{0,0,0,0}};
    vector<vector<int>> build_frame8 = {{0,0,0,1},{0,1,1,1},{0,1,0,1},{1,0,0,1},{0,0,0,0}};
    vector<vector<int>> build_frame9 = {{1,0,0,1},{0,1,1,1},{1,1,1,1},
                                        {0,1,0,1},{2,1,0,1},{0,2,1,1},
                                        {1,2,1,1},{1,2,0,1}};
    vector<vector<int>> build_frame10 = {{1,0,0,1},{0,1,1,1},{1,1,1,1},
                                        {0,1,0,1},{2,1,0,1},{0,2,1,1},
                                        {1,2,1,1},{1,2,0,1},{1,2,1,0}};
    vector<vector<int>> build_frame11 = {{0,2,0,1},{0,4,1,1}};
    vector<vector<int>> build_frame12 = {{0,0,0,1},{0,1,1,1},{1,1,0,1},{0,2,1,1},{1,1,0,0},{0,2,1,0},{1,2,0,1}};

    vector<vector<int>> result1 = solution(n,build_frame12);


    for (auto a : result1)
    {
        for(auto b : a)
        {
            cout<<b<<" ";
        }
        cout<<endl;
    }
}