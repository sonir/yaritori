//
//  Csv2Buffer.cpp
//  yaritori
//
//  Created by sonir on 1/31/18.
//
//

#include "Csv2Buffer.hpp"

void Csv2Buffer :: test () {
    
    cout << "Csv3Buffers :: test" << endl;
    
}



void Csv2Buffer::createAgents(ag_t *agents){
    
    
    //Create a vector to storage scenes
    // vector<ag_t> scenes;
    //Path to the comma delimited file
    string filePath = "0-agents.csv";
    

     //Load file placed in bin/data
     ofFile file(filePath);
     if(!file.exists()){
     ofLogError("The file " + filePath + " is missing");
     }
     
     ofBuffer buffer(file);
     int count = AG_NUM_OFFSET;
     
     //Read file line by line
     for (ofBuffer::Line it = buffer.getLines().begin(), end = buffer.getLines().end(); it != end; ++it) {
         string line = *it;
         //Ignore first line of CSV
         if (buffer.getLines().begin() == it){
         
            continue;
         
         }
         //Split line into strings
         vector<string> words = ofSplitString(line, ",");
         
         //Store strings into a custom container
         if (words.size()>=2) {
         
             //Storage the params into a struct
             ag_t *elm = agents;
             
             elm->agid = count; //std::stoi(nullCheck(words[0]));
             elm->active = (bool)std::stoi(nullCheck(words[LOG_ACTIVE]));
             elm->posi.x = std::stof(nullCheck(words[LOG_POSI_X]));
             elm->posi.y = std::stof(nullCheck(words[LOG_POSI_Y]));
             elm->size = std::stof(nullCheck(words[LOG_SIZE]));
             elm->view = std::stof(nullCheck(words[LOG_VIEW]));
             elm->mov = std::stof(nullCheck(words[LOG_MOV]));
             elm->condition = (condition_e)std::stoi(nullCheck(words[LOG_CONDITION]));
             elm->spd.x = std::stof(nullCheck(words[LOG_SPD_X]));
             elm->spd.y = std::stof(nullCheck(words[LOG_SPD_Y]));
             elm->interact_with = std::stoi(nullCheck(words[LOG_INTERACT_WITH]));
             
             //Set the struct to vector
             agents++;
             count++;
         
         }
     } //End of for
     
    gismo.agents.count += count;
    
    
}



string Csv2Buffer::nullCheck(string word){
    
    if(word == "\0"){
        cout << "ERR : null value was detected in CSV." << endl;
        word = "0";
    }
    return word;
}
