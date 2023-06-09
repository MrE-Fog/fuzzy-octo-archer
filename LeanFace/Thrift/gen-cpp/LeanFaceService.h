/**
 * Autogenerated by Thrift Compiler (0.9.2)
 *
 * DO NOT EDIT UNLESS YOU ARE SURE THAT YOU KNOW WHAT YOU ARE DOING
 *  @generated
 */
#ifndef LeanFaceService_H
#define LeanFaceService_H

//#include <thrift/TDispatchProcessor.h>
#include "../thrift-cpp/TDispatchProcessor.h"
#include "LeanFace_types.h"

namespace leanface {

class LeanFaceServiceIf {
 public:
  virtual ~LeanFaceServiceIf() {}
  virtual int32_t lean_face(const std::string& inputImgName, const std::string& ouputImgName) = 0;
};

class LeanFaceServiceIfFactory {
 public:
  typedef LeanFaceServiceIf Handler;

  virtual ~LeanFaceServiceIfFactory() {}

  virtual LeanFaceServiceIf* getHandler(const ::apache::thrift::TConnectionInfo& connInfo) = 0;
  virtual void releaseHandler(LeanFaceServiceIf* /* handler */) = 0;
};

class LeanFaceServiceIfSingletonFactory : virtual public LeanFaceServiceIfFactory {
 public:
  LeanFaceServiceIfSingletonFactory(const boost::shared_ptr<LeanFaceServiceIf>& iface) : iface_(iface) {}
  virtual ~LeanFaceServiceIfSingletonFactory() {}

  virtual LeanFaceServiceIf* getHandler(const ::apache::thrift::TConnectionInfo&) {
    return iface_.get();
  }
  virtual void releaseHandler(LeanFaceServiceIf* /* handler */) {}

 protected:
  boost::shared_ptr<LeanFaceServiceIf> iface_;
};

class LeanFaceServiceNull : virtual public LeanFaceServiceIf {
 public:
  virtual ~LeanFaceServiceNull() {}
  int32_t lean_face(const std::string& /* inputImgName */, const std::string& /* ouputImgName */) {
    int32_t _return = 0;
    return _return;
  }
};

typedef struct _LeanFaceService_lean_face_args__isset {
  _LeanFaceService_lean_face_args__isset() : inputImgName(false), ouputImgName(false) {}
  bool inputImgName :1;
  bool ouputImgName :1;
} _LeanFaceService_lean_face_args__isset;

class LeanFaceService_lean_face_args {
 public:

  static const char* ascii_fingerprint; // = "07A9615F837F7D0A952B595DD3020972";
  static const uint8_t binary_fingerprint[16]; // = {0x07,0xA9,0x61,0x5F,0x83,0x7F,0x7D,0x0A,0x95,0x2B,0x59,0x5D,0xD3,0x02,0x09,0x72};

  LeanFaceService_lean_face_args(const LeanFaceService_lean_face_args&);
  LeanFaceService_lean_face_args& operator=(const LeanFaceService_lean_face_args&);
  LeanFaceService_lean_face_args() : inputImgName(), ouputImgName() {
  }

  virtual ~LeanFaceService_lean_face_args() throw();
  std::string inputImgName;
  std::string ouputImgName;

  _LeanFaceService_lean_face_args__isset __isset;

  void __set_inputImgName(const std::string& val);

  void __set_ouputImgName(const std::string& val);

  bool operator == (const LeanFaceService_lean_face_args & rhs) const
  {
    if (!(inputImgName == rhs.inputImgName))
      return false;
    if (!(ouputImgName == rhs.ouputImgName))
      return false;
    return true;
  }
  bool operator != (const LeanFaceService_lean_face_args &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const LeanFaceService_lean_face_args & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

  friend std::ostream& operator<<(std::ostream& out, const LeanFaceService_lean_face_args& obj);
};


class LeanFaceService_lean_face_pargs {
 public:

  static const char* ascii_fingerprint; // = "07A9615F837F7D0A952B595DD3020972";
  static const uint8_t binary_fingerprint[16]; // = {0x07,0xA9,0x61,0x5F,0x83,0x7F,0x7D,0x0A,0x95,0x2B,0x59,0x5D,0xD3,0x02,0x09,0x72};


  virtual ~LeanFaceService_lean_face_pargs() throw();
  const std::string* inputImgName;
  const std::string* ouputImgName;

  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

  friend std::ostream& operator<<(std::ostream& out, const LeanFaceService_lean_face_pargs& obj);
};

typedef struct _LeanFaceService_lean_face_result__isset {
  _LeanFaceService_lean_face_result__isset() : success(false) {}
  bool success :1;
} _LeanFaceService_lean_face_result__isset;

class LeanFaceService_lean_face_result {
 public:

  static const char* ascii_fingerprint; // = "32183C4A04E706C58ED2F62566DDD8DE";
  static const uint8_t binary_fingerprint[16]; // = {0x32,0x18,0x3C,0x4A,0x04,0xE7,0x06,0xC5,0x8E,0xD2,0xF6,0x25,0x66,0xDD,0xD8,0xDE};

  LeanFaceService_lean_face_result(const LeanFaceService_lean_face_result&);
  LeanFaceService_lean_face_result& operator=(const LeanFaceService_lean_face_result&);
  LeanFaceService_lean_face_result() : success(0) {
  }

  virtual ~LeanFaceService_lean_face_result() throw();
  int32_t success;

  _LeanFaceService_lean_face_result__isset __isset;

  void __set_success(const int32_t val);

  bool operator == (const LeanFaceService_lean_face_result & rhs) const
  {
    if (!(success == rhs.success))
      return false;
    return true;
  }
  bool operator != (const LeanFaceService_lean_face_result &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const LeanFaceService_lean_face_result & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

  friend std::ostream& operator<<(std::ostream& out, const LeanFaceService_lean_face_result& obj);
};

typedef struct _LeanFaceService_lean_face_presult__isset {
  _LeanFaceService_lean_face_presult__isset() : success(false) {}
  bool success :1;
} _LeanFaceService_lean_face_presult__isset;

class LeanFaceService_lean_face_presult {
 public:

  static const char* ascii_fingerprint; // = "32183C4A04E706C58ED2F62566DDD8DE";
  static const uint8_t binary_fingerprint[16]; // = {0x32,0x18,0x3C,0x4A,0x04,0xE7,0x06,0xC5,0x8E,0xD2,0xF6,0x25,0x66,0xDD,0xD8,0xDE};


  virtual ~LeanFaceService_lean_face_presult() throw();
  int32_t* success;

  _LeanFaceService_lean_face_presult__isset __isset;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);

  friend std::ostream& operator<<(std::ostream& out, const LeanFaceService_lean_face_presult& obj);
};

class LeanFaceServiceClient : virtual public LeanFaceServiceIf {
 public:
  LeanFaceServiceClient(boost::shared_ptr< ::apache::thrift::protocol::TProtocol> prot) {
    setProtocol(prot);
  }
  LeanFaceServiceClient(boost::shared_ptr< ::apache::thrift::protocol::TProtocol> iprot, boost::shared_ptr< ::apache::thrift::protocol::TProtocol> oprot) {
    setProtocol(iprot,oprot);
  }
 private:
  void setProtocol(boost::shared_ptr< ::apache::thrift::protocol::TProtocol> prot) {
  setProtocol(prot,prot);
  }
  void setProtocol(boost::shared_ptr< ::apache::thrift::protocol::TProtocol> iprot, boost::shared_ptr< ::apache::thrift::protocol::TProtocol> oprot) {
    piprot_=iprot;
    poprot_=oprot;
    iprot_ = iprot.get();
    oprot_ = oprot.get();
  }
 public:
  boost::shared_ptr< ::apache::thrift::protocol::TProtocol> getInputProtocol() {
    return piprot_;
  }
  boost::shared_ptr< ::apache::thrift::protocol::TProtocol> getOutputProtocol() {
    return poprot_;
  }
  int32_t lean_face(const std::string& inputImgName, const std::string& ouputImgName);
  void send_lean_face(const std::string& inputImgName, const std::string& ouputImgName);
  int32_t recv_lean_face();
 protected:
  boost::shared_ptr< ::apache::thrift::protocol::TProtocol> piprot_;
  boost::shared_ptr< ::apache::thrift::protocol::TProtocol> poprot_;
  ::apache::thrift::protocol::TProtocol* iprot_;
  ::apache::thrift::protocol::TProtocol* oprot_;
};

class LeanFaceServiceProcessor : public ::apache::thrift::TDispatchProcessor {
 protected:
  boost::shared_ptr<LeanFaceServiceIf> iface_;
  virtual bool dispatchCall(::apache::thrift::protocol::TProtocol* iprot, ::apache::thrift::protocol::TProtocol* oprot, const std::string& fname, int32_t seqid, void* callContext);
 private:
  typedef  void (LeanFaceServiceProcessor::*ProcessFunction)(int32_t, ::apache::thrift::protocol::TProtocol*, ::apache::thrift::protocol::TProtocol*, void*);
  typedef std::map<std::string, ProcessFunction> ProcessMap;
  ProcessMap processMap_;
  void process_lean_face(int32_t seqid, ::apache::thrift::protocol::TProtocol* iprot, ::apache::thrift::protocol::TProtocol* oprot, void* callContext);
 public:
  LeanFaceServiceProcessor(boost::shared_ptr<LeanFaceServiceIf> iface) :
    iface_(iface) {
    processMap_["lean_face"] = &LeanFaceServiceProcessor::process_lean_face;
  }

  virtual ~LeanFaceServiceProcessor() {}
};

class LeanFaceServiceProcessorFactory : public ::apache::thrift::TProcessorFactory {
 public:
  LeanFaceServiceProcessorFactory(const ::boost::shared_ptr< LeanFaceServiceIfFactory >& handlerFactory) :
      handlerFactory_(handlerFactory) {}

  ::boost::shared_ptr< ::apache::thrift::TProcessor > getProcessor(const ::apache::thrift::TConnectionInfo& connInfo);

 protected:
  ::boost::shared_ptr< LeanFaceServiceIfFactory > handlerFactory_;
};

class LeanFaceServiceMultiface : virtual public LeanFaceServiceIf {
 public:
  LeanFaceServiceMultiface(std::vector<boost::shared_ptr<LeanFaceServiceIf> >& ifaces) : ifaces_(ifaces) {
  }
  virtual ~LeanFaceServiceMultiface() {}
 protected:
  std::vector<boost::shared_ptr<LeanFaceServiceIf> > ifaces_;
  LeanFaceServiceMultiface() {}
  void add(boost::shared_ptr<LeanFaceServiceIf> iface) {
    ifaces_.push_back(iface);
  }
 public:
  int32_t lean_face(const std::string& inputImgName, const std::string& ouputImgName) {
    size_t sz = ifaces_.size();
    size_t i = 0;
    for (; i < (sz - 1); ++i) {
      ifaces_[i]->lean_face(inputImgName, ouputImgName);
    }
    return ifaces_[i]->lean_face(inputImgName, ouputImgName);
  }

};

} // namespace

#endif
