#include <string>
#include <memory>

namespace m1{

    class Error{
    public:
        virtual std::string HierarchyId(){
            return "";
        };
        virtual std::string Description(){
            return "";
        }
        virtual bool IsError(){
            return false;
        }
    };

    class ErrorImpl : public Error{
    public:
        ErrorImpl(std::string id, std::string description, Error child){
            _hierarchyId = id;
            _description = description;
            if(child.IsError()){
                _hierarchyId += child.HierarchyId();
                _description += ": " + child.Description();
            }
            _child = child;
            _isError = true;
        }

        ErrorImpl(){
            _isError = false;
        }

        std::string HierarchyId() override{
            return _hierarchyId;
        }

        std::string Description() override{
            return _description;
        }

        bool IsError() override{
            return _isError;
        }

    private:
        bool _isError;
        std::string _id;
        std::string _description;
        Error _child;
        std::string _hierarchyId;
    };
}
