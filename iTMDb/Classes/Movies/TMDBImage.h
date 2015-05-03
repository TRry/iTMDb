//
//  TMDBImage.h
//  iTMDb
//
//  Created by Christian Rasmussen on 07/11/10.
//  Copyright (c) 2010 Devify. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreGraphics/CoreGraphics.h>

typedef NS_ENUM(NSUInteger, TMDBImageType) {
	TMDBImageTypePoster,
	TMDBImageTypeBackdrop
};

/**
 * 
 */
typedef NS_ENUM(NSUInteger, TMDBImageSize) {
	TMDBImageSizeOriginal,
	TMDBImageSizeWidth,
	TMDBImageSizeHeight
};

/**
 * A `TMDBImage` object represents an image in one-to-many sizes.
 */
@interface TMDBImage : NSObject

@property (nonatomic, readonly) TMDBImageType type;
@property (nonatomic, readonly) CGSize originalSize;
@property (nonatomic, copy, readonly) NSString *iso639_1; // Two-letter language code

@property (nonatomic, readonly) float voteAverage;
@property (nonatomic, readonly) NSUInteger voteCount;

/** @name Creating `TMDBImage` instances */

+ (NSArray *)imageArrayWithRawImageDictionaries:(NSArray *)rawImages ofType:(TMDBImageType)aType;

- (instancetype)initWithDictionary:(NSDictionary *)rawImageData type:(TMDBImageType)type NS_DESIGNATED_INITIALIZER;

/** @name Getting URLs */

- (NSURL *)urlForSize:(NSString *)size;

/** @name Getting Sizes */

/**
 * Returns the width or height of an image size string. If no size is explicitly
 * specified, such as the `original` size, `-1` is returned. The dimension, i.e.
 * either width or height (or original) is put in the `outImageSize` parameter.
 *
 * @return `-1` if no valid size could be found, or if it is the original size.
 */
+ (CGFloat)sizeFromString:(NSString *)s imageSize:(TMDBImageSize *)outImageSize;

/**
 * Returns the size from `sizes` that closest matches the specified `size`.
 *
 * The size equal to or larger than the specified `size`, or if none such exist
 * the size that matches the closest, is returned.
 *
 * @param size The size in pixels that should be returned in string form.
 * @param sizes An array of `NSString`s that should be enumerated. Valid values
 * can be found in the `TMDBConfiguration` instance, such as `imagesPosterSizes`.
 * @param dimension The dimension (width, height or original) that should be
 * returned.
 * @return An `NSString` representing the `size` in the specified `dimension`,
 * or nil if no such exist.
 */
+ (NSString *)sizeClosestMatchingSize:(float)size inSizes:(NSArray *)sizes dimension:(TMDBImageSize)dimension;

@end

@interface TMDBImage (UnavailableMethods)

@property (nonatomic, copy, readonly) NSString *id UNAVAILABLE_ATTRIBUTE;

+ (TMDBImage *)imageWithId:(NSString *)anID ofType:(TMDBImageType)type UNAVAILABLE_ATTRIBUTE;
- (instancetype)initWithID:(NSString *)anID ofType:(TMDBImageType)type UNAVAILABLE_ATTRIBUTE;

- (CGSize)sizeForSize:(NSString *)size UNAVAILABLE_ATTRIBUTE;

@end
