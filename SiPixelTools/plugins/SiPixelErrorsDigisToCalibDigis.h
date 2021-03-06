#ifndef SiPixelErrorsDigisToCalibDigis_h
#define SiPixelErrorsDigisToCalibDigis_h

/**  class SiPixelErrorsDigisToCalibDigis

Description: Create monitorElements for the Errors in created in the reduction of digis to calibDigis

**/

// Original Author: Ricardo Vasquez Sierra on April 9, 2008


// system include files
#include <memory>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/Framework/interface/ESHandle.h"

#include "FWCore/Utilities/interface/InputTag.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"

#include "DataFormats/Common/interface/DetSetVector.h"
#include "DataFormats/DetId/interface/DetId.h"

#include "DataFormats/SiPixelDigi/interface/SiPixelCalibDigi.h"
#include "DataFormats/SiPixelDigi/interface/SiPixelCalibDigiError.h"

#include "DQMServices/Core/interface/DQMStore.h"
#include "DQMServices/Core/interface/MonitorElement.h"

#include "CalibTracker/SiPixelTools/interface/SiPixelHistogramIdGC.h"


#include "CalibTracker/SiPixelTools/interface/SiPixelFolderOrganizerGC.h" 

#include "Geometry/TrackerGeometryBuilder/interface/TrackerGeometry.h"
#include "Geometry/TrackerGeometryBuilder/interface/PixelGeomDetUnit.h"
#include "Geometry/TrackerGeometryBuilder/interface/PixelGeomDetType.h"
#include "Geometry/Records/interface/TrackerDigiGeometryRecord.h" 

#include "CondFormats/SiPixelObjects/interface/SiPixelFedCablingMap.h"


#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"


//
// class declaration
//

class SiPixelErrorsDigisToCalibDigis : public edm::EDAnalyzer {
 public:
  explicit SiPixelErrorsDigisToCalibDigis(const edm::ParameterSet&);
  ~SiPixelErrorsDigisToCalibDigis();
  
  MonitorElement*  bookDQMHistogram2D(uint32_t detid, std::string name, std::string title, int nchX, double lowX, double highX, int nchY, double lowY, double highY);      
  MonitorElement*  bookDQMHistoPlaquetteSummary2D(uint32_t detid, std::string name,std::string title); // take the detid to determine the size of rows and columns, this saves looking up everything in the cabling map by the user. 
  
  TH2F*  bookHistogram2D(uint32_t detid, std::string name, std::string title, int nchX, double lowX, double highX, int nchY, double lowY, double highY);      
  TH2F*  bookHistoPlaquetteSummary2D(uint32_t detid, std::string name,std::string title); // take the detid to determine the size of rows and columns, this saves looking up everything in the cabling map by the user. 
  

  bool setDQMDirectory(std::string dirName);	
  bool setDQMDirectory(uint32_t detID); //automatically create directory hierachy based on DetID 
  void GetPixelDirectory(uint32_t detID);

 protected:
  
       edm::ESHandle<TrackerGeometry> geom_;

   private:
      virtual void beginJob() ;
      virtual void analyze(const edm::Event&, const edm::EventSetup&);
      virtual void endJob() ;
      std::map<std::string, TFileDirectory>  myTFileDirMap_;
      // ----------member data ---------------------------

      // store the number of error per detector id encountered
      // store the location of the mismatching error in the detector id

      edm::InputTag siPixelProducerLabel_;
      edm::EDGetTokenT <edm::DetSetVector<SiPixelCalibDigiError> > tPixelCalibDigiError;

      DQMStore* daqBE_;
      SiPixelHistogramId * theHistogramIdWorker_;
      std::string outputFilename_;
      bool createOutputFile_;

      SiPixelFolderOrganizerGC* folderMaker_;
      std::map<uint32_t, TH2F*> SiPixelErrorsDigisToCalibDigis_2DErrorInformation_; 
      
      TH2F * temp;
      edm::Service<TFileService> fs;
     
};

#endif
