
#ifndef Globos_h
#define Globos_h

#include "FWCore/Framework/interface/EDAnalyzer.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include <Rtypes.h>
#include <string>
#include <vector>

//DQM
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "DQMServices/Core/interface/DQMEDAnalyzer.h"
#include "DQMServices/Core/interface/DQMEDHarvester.h"
#include "DQMServices/Core/interface/DQMStore.h"

class Globos {
public:
  typedef dqm::legacy::DQMStore DQMStore;
  typedef dqm::legacy::MonitorElement MonitorElement;
  void setBookEfficiencyFlag(const bool &);
  bool bookEfficiencyFlag_ = false;

protected:
  explicit Globos(const edm::ParameterSet &conf);
  ~Globos(); // override;

  // utility methods
  void setBookPrefix(const std::string &);
  void setBookIndex(short);
  void setBookStatOverflowFlag(const bool &);
  std::string newName(const std::string &name);
  int verbosity() { return verbosity_; }

  bool histoNamesReady;
  std::string finalStep_;
  std::string inputFile_;
  std::string outputFile_;
  std::string inputInternalPath_;
  std::string outputInternalPath_;

  // Common features for ElectronDqmAnalyzerBase/ElectronDqmHarvesterBase
  MonitorElement *bookH1(DQMStore::IBooker &,
                         const std::string &name,
                         const std::string &title,
                         int nchX,
                         double lowX,
                         double highX,
                         const std::string &titleX = "",
                         const std::string &titleY = "Events",
                         Option_t *option = "E1 P");/**/

  MonitorElement *bookH1withSumw2(DQMStore::IBooker &,
                                  const std::string &name,
                                  const std::string &title,
                                  int nchX,
                                  double lowX,
                                  double highX,
                                  const std::string &titleX = "",
                                  const std::string &titleY = "Events",
                                  Option_t *option = "E1 P");

  MonitorElement *bookH2(DQMStore::IBooker &,
                         const std::string &name,
                         const std::string &title,
                         int nchX,
                         double lowX,
                         double highX,
                         int nchY,
                         double lowY,
                         double highY,
                         const std::string &titleX = "",
                         const std::string &titleY = "",
                         Option_t *option = "COLZ");

  MonitorElement *bookH2withSumw2(DQMStore::IBooker &,
                                  const std::string &name,
                                  const std::string &title,
                                  int nchX,
                                  double lowX,
                                  double highX,
                                  int nchY,
                                  double lowY,
                                  double highY,
                                  const std::string &titleX = "",
                                  const std::string &titleY = "",
                                  Option_t *option = "COLZ");

  MonitorElement *bookP1(DQMStore::IBooker &,
                         const std::string &name,
                         const std::string &title,
                         int nchX,
                         double lowX,
                         double highX,
                         double lowY,
                         double highY,
                         const std::string &titleX = "",
                         const std::string &titleY = "",
                         Option_t *option = "E1 P");



  // Features for ElectronDqmHarvesterBase
private:
  std::string bookPrefix_;
  short bookIndex_;
  bool bookStatOverflowFlag_ = false;
  int verbosity_;

};

#endif
