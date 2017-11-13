#ifndef TBANKDECODER
#define TBANKDECODER

#include <string>
#include <typeinfo>
#include <type_traits>
#include <vector>

/// \brief Abstract implementation of an MDF bank decoder.
/// TMDFDataSource uses concrete TBankDecoder implementations to read banks.
class TBankDecoder {
public:
   virtual ~TBankDecoder() {}
   /// Retrieve bank name. Corresponds to the column name used in TDataFrame to refer to this bank.
   virtual std::string GetName() const = 0;
   /// Retrieve the type name of this bank as a string.
   virtual std::string GetTypeName() const = 0;
   /// Retrieve the type info of this bank.
   virtual const std::type_info &GetTypeInfo() const = 0;
   /// Retrieve bank ID.
   virtual int GetID() const = 0;
   /// Take a bank body as raw bytes, put the encoding in the area of memory pointed by destination
   virtual void Decode(const char *bank, void *destination) const = 0;
   /// Allocate N objects of the correct type, after checking that we expect the right type
   virtual void *Allocate() const = 0;
   /// Deallocate objects by calling the destructor for the appropriate type
   virtual void Deallocate(void *obj) const = 0;
};

#endif
