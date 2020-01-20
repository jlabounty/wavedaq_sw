#include <string>
#include <map>
#include <vector>
#include <iostream>
#include <sstream>

class Property;

#ifndef PROPERTIES_H
#define PROPERTIES_H

// --- Property --- single property
class Property{
   protected:
      std::string fStringVal;
      std::vector<int> fIntVal;
      bool fBoolVal;
      std::vector<unsigned int> fUIntVal;
      std::vector<float> fFloatVal;
      bool fChanged;
      bool fIntConverted;
      bool fBoolConverted;
      bool fUIntConverted;
      bool fHexConverted;
      bool fUHexConverted;
      bool fFloatConverted;

      template <class T> void PropertyToArray(std::vector<T> &destination, std::ios_base::fmtflags f=(std::ios_base::fmtflags )0){
         destination.clear();
         std::stringstream ss;
         ss << fStringVal;

         std::string token;

         while(std::getline(ss, token, ',')) {
            std::stringstream token_ss(token);
            if(f) token_ss.setf(f, std::ios_base::basefield);
            T value;
            if(token_ss >> value){
               destination.push_back(value);
            }
         }
      }

      void PropertyToBool(){
         if(fStringVal.rfind('y',0)==0 || fStringVal.rfind("true",0)==0)
            fBoolVal = true;
         else
            fBoolVal = false;
      }

   public:
      //Setter and Getter
      void SetStringValue(std::string value){
         fStringVal = value;
         fChanged = true;
         fIntConverted = false;
         fBoolConverted = false;
         fHexConverted = false;
         fUIntConverted = false;
         fUHexConverted = false;
         fFloatConverted = false;
      }

      std::string GetStringValue(){
         return fStringVal;
      }

      bool IsChanged(){
         return fChanged;
      }

      void RemoveChanged(){
         fChanged = false;
      }

      //Methods
      void ConvertInt(){
         PropertyToArray<int>(fIntVal);
         fIntConverted = true;
         fHexConverted = false;
      }

      const int* GetIntVector(long *size){
         if(! fIntConverted) {
            ConvertInt();
         }
         *size = fIntVal.size();
         return fIntVal.data();
      }

      int GetInt(){
         long size;
         const int *v = GetIntVector(&size);
         if(size) return v[0];
         else return -1;
      }

      void ConvertHex(){
         PropertyToArray<int>(fIntVal, std::ios_base::hex);
         fHexConverted = true;
         fIntConverted = false;
      }

      const int* GetHexVector(long *size){
         if(! fHexConverted) {
            ConvertHex();
         }
         *size = fIntVal.size();
         return fIntVal.data();
      }

      int GetHex(){
         long size;
         const int *v = GetHexVector(&size);
         if(size) return v[0];
         else return -1;
      }

      void ConvertUInt(){
         PropertyToArray<unsigned int>(fUIntVal);
         fUIntConverted = true;
         fUHexConverted = false;
      }

      const unsigned int* GetUIntVector(long *size){
         if(! fUIntConverted) {
            ConvertUInt();
         }
         *size = fUIntVal.size();
         return fUIntVal.data();
      }

      int GetUInt(){
         long size;
         const unsigned int *v = GetUIntVector(&size);
         if(size) return v[0];
         else return -1;
      }

      void ConvertUHex(){
         PropertyToArray<unsigned int>(fUIntVal, std::ios_base::hex);
         fUHexConverted = true;
         fUIntConverted = false;
      }

      const unsigned int* GetUHexVector(long *size){
         if(! fUHexConverted) {
            ConvertUHex();
         }
         *size = fUIntVal.size();
         return fUIntVal.data();
      }

      unsigned int GetUHex(){
         long size;
         const unsigned int *v = GetUHexVector(&size);
         if(size) return v[0];
         else return -1;
      }

      void ConvertBool(){
         PropertyToBool();
         fBoolConverted = true;
      }

      bool GetBool(){
         if(! fBoolConverted) {
            ConvertBool();
         }
         return fBoolVal;
      }

      void ConvertFloat(){
         PropertyToArray<float>(fFloatVal, std::ios_base::hex);
         fFloatConverted = true;
      }

      const float* GetFloatVector(long *size){
         if(! fFloatConverted) {
            ConvertFloat();
         }
         *size = fFloatVal.size();
         return fFloatVal.data();
      }

      float GetFloat(){
         long size;
         const float *v = GetFloatVector(&size);
         if(size) return v[0];
         else return -1;
      }

      //Constructor
      Property(){
         fChanged = true;
         fIntConverted = false;
         fHexConverted = false;
         fFloatConverted = false;
      }

      //Destructor
      virtual ~Property(){
      }

};

// --- PropertyGroup --- contains a map of properties
class PropertyGroup : std::map<std::string,Property>{
   protected:

   public:
      using std::map<std::string,Property>::at;
      using std::map<std::string,Property>::operator[];
      using std::map<std::string,Property>::size;
      using std::map<std::string,Property>::clear;
      using std::map<std::string,Property>::begin;
      using std::map<std::string,Property>::end;

      bool contains(std::string val){
         if(find(val)==end())
            return false;
         else
            return true;
         
      }

      //Constructor
      PropertyGroup(){
      }

      //Destructor
      virtual ~PropertyGroup(){
      }
};

#endif
