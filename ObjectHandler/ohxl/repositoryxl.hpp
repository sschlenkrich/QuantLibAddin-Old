
/*
 Copyright (C) 2005, 2006, 2007 Eric Ehlers

 This file is part of QuantLib, a free-software/open-source library
 for financial quantitative analysts and developers - http://quantlib.org/

 QuantLib is free software: you can redistribute it and/or modify it under the
 terms of the QuantLib license.  You should have received a copy of the
 license along with this program; if not, please email quantlib-dev@lists.sf.net
 The license is also available online at http://quantlib.org/html/license.html

 This program is distributed in the hope that it will be useful, but WITHOUT
 ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 FOR A PARTICULAR PURPOSE.  See the license for more details.
*/

/*! \file
    \brief Class RepositoryXL - Excel-specific enhancements to the Repository class.
*/

#ifndef ohxl_repositoryxl_hpp
#define ohxl_repositoryxl_hpp

#include <oh/repository.hpp>
#include <xlsdk/xlsdkdefines.hpp>
#include <ohxl/ohxldefines.hpp>
#include <ohxl/objectxl.hpp>

namespace ObjectHandler {

    //! Excel-specific enhancements to the Repository class.
    /*! Extends the base Repository class to work with ObjectXL instead of
        Object, and to provide other functionality specific to the Excel platform.
    */
    class DLL_API RepositoryXL : public Repository {
    public:
    static RepositoryXL &instance();

        //! \name Object Management
        //@{
        //! Wrapper for the storeObject function in the base class.
        /*! Initialize the CallingRange object associated with the new ObjectXL object.
            Perform a test to ensure that an object from one cell cannot overwrite
            an object in another cell with the same ID.
        */
        virtual std::string storeObject(const std::string &objectID, 
                                        const boost::shared_ptr<Object> &object);
        //! Implementation of the retrieveObject function.
        /*! Convert Excel-format Object IDs into the format reconized by the base
            Repository class.  Recast references from Object to ObjectXL.
        */
        virtual boost::shared_ptr<Object> retrieveObjectImpl(
            const std::string &objectID) const;

        //! Wrapper for the deleteObject function in the base class.
        /*! Convert Excel-format Object IDs into the format reconized by the base
            Repository class.
        */
        virtual void deleteObject(const std::string &objectID);
        //@}

        //! \name Error Messages
        //@{
        //! Log an error message.
        void logError(const std::string &message, const bool &append = false);
        //! Retrieve the error associated with the given range.
        std::string retrieveError(const XLOPER *range);
        //! Clear any error associated with the given range.
        void clearError();
        //@}

        //! \name Logging
        //@{
        //! Write the entire contents of the RepositoryXL object to the given stream.
        /*! Call the corresponding function in the base class, then output additional info
            specific to the Excel platform, e.g. information on CallingRange objects.
        */
        virtual void dump(std::ostream&);
        //! Write the indicated Object to the given stream.
        virtual void dumpObject(const std::string &objectID, std::ostream&);
        //@}

        //! \name Garbage Collection
        //@{
        //! Delete all objects orphaned by the deletion of the calling cell.
        /*! By default this function does not delete permanent objects.  Setting
            deletePermanent to true causes permanent objects to be garbage
            collected as well.
        */
        void collectGarbage(const bool &deletePermanent = false);
        //@}

        //! \name Calling Ranges
        //@{
        //! Retrieve the address of the cell in which the given object resides.
        std::string callerAddress(const std::string &objectID);
        //! Retrieve key of CallingRange object associated with the given object.
        std::string callerKey(const std::string &objectID);
        //@}

    private:
        boost::shared_ptr<CallingRange> getCallingRange();

    };

}

#endif
