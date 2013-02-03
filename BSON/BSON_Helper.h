//
//  BSON_Helper.h
//  ObjCMongoDB
//
//  Copyright 2012 Paul Melnikow and other contributors
//
//  Licensed under the Apache License, Version 2.0 (the "License");
//  you may not use this file except in compliance with the License.
//  You may obtain a copy of the License at
//
//  http://www.apache.org/licenses/LICENSE-2.0
//
//  Unless required by applicable law or agreed to in writing, software
//  distributed under the License is distributed on an "AS IS" BASIS,
//  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
//  See the License for the specific language governing permissions and
//  limitations under the License.
//

#import <Foundation/Foundation.h>
#import "BSONIterator.h"

#if __has_feature(objc_arc)
#define maybe_autorelease_and_return(x) return x
#define maybe_retain_autorelease_and_return(x) return x;
#else
#define maybe_autorelease_and_return(x) return [x autorelease];
#define maybe_retain_autorelease_and_return(x) return [[x retain] autorelease];
#endif

/**
 Raises an exception for a nil key.
 @param key The key to test
 */
void BSONAssertKeyNonNil (NSString *key);

/**
 Raises an exception for key which is illegal in MongoDB.
 @param key The key to test
 */
void BSONAssertKeyLegalForMongoDB(NSString *key);

/**
 Raises an exception for a nil value.
 @param key The value to test
 */
void BSONAssertValueNonNil (id key);

/**
 Raises an exception if the iterator's native value type doesn't match the
 expected type.
 @param iterator A BSON iterator
 @param valueType The expected native value type
 */
void BSONAssertIteratorIsValueType (BSONIterator * iterator, bson_type valueType);

/**
 Raises an exception if the iterator's native value type doesn't match one of the
 expected types.
 @param iterator A BSON iterator
 @param valueType A C array of allowed native value types
 */
void BSONAssertIteratorIsInValueTypeArray (BSONIterator * iterator, bson_type * valueType);

/**
 Returns a string representation of a native BSON type.
 @param t A native BSON type
 @return A string representation of the BSON type
 */
__autoreleasing NSString * NSStringFromBSONType (bson_type t);

__autoreleasing NSString * NSStringFromBSONError(int err);

/**
 Returns a string representation of a BSON document, for debugging purposes.
 
 This function invokes printing behavior of the native BSON code.
 @param b A pointer to a native BSON struct
 @return A string representation of the BSON document
 */
__autoreleasing NSString * NSStringFromBSON (const bson * b);

/**
 Returns an autoreleased NSData object which provides access to the BSON object.
 
 If <code>copy</code> is <code>YES</code>, the NSData object allocates a new buffer and
 copies the contents.
 
 If <code>NO</code>, the NSData object simply points to data buffer of the native BSON
 object, without copying or transferring ownership. The returned object will stop working
 if the BSON object is deallocated or subsequently modified. This option is intended for
 temporary use.
 
 @param b A pointer to a native BSON struct
 @param copy A BOOL indicating whether to copy the document's data buffer
 @return An NSData instance which provides access to the BSON document's data buffer or
   a copy of that data buffer
*/
__autoreleasing NSData * NSDataFromBSON (const bson * b, BOOL copy);