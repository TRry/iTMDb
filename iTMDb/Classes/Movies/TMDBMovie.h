//
//  TMDBMovie.h
//  iTMDb
//
//  Created by Christian Rasmussen on 04/11/10.
//  Copyright (c) 2010 Devify. All rights reserved.
//

#import <Foundation/Foundation.h>

typedef NS_OPTIONS(NSUInteger, TMDBMovieFetchOptions) {
	TMDBMovieFetchOptionBasic    = 1 << 1,
	TMDBMovieFetchOptionCasts    = 1 << 2,
	TMDBMovieFetchOptionKeywords = 1 << 3,
	TMDBMovieFetchOptionImages   = 1 << 4,
	TMDBMovieFetchOptionAll      = TMDBMovieFetchOptionBasic    |
								   TMDBMovieFetchOptionCasts    |
								   TMDBMovieFetchOptionKeywords |
								   TMDBMovieFetchOptionImages
};

typedef void (^TMDBMovieFetchCompletionBlock)(NSError *error);

/**
 * A `TMDBMovie` object represents information about a movie from the
 * [TMDb](http://themoviedb.org/) website. It is responsible for updating 
 * itself.
 *
 * All properties are readonly, as the iTMDb framework does not support editing
 * the TMDb website. Your application should fetch movie information using the
 * TMDBMovie class and then use or copy the results to your own model objects.
 */
@interface TMDBMovie : NSObject

#pragma mark - Creating an Instance
/** @name Creating an Instance */

/**
 * Creates an empty movie object ready to be loaded, based on the provided TMDb
 * ID.
 *
 * You must call either `-load` or `-populate:` to populate the object with
 * data.
 *
 * @param tmdbID The TMDb ID of the movie to be looked up.
 * @return An empty movie object ready to be loaded.
 */
- (instancetype)initWithID:(NSUInteger)tmdbID NS_DESIGNATED_INITIALIZER;

/**
 * Creates an empty movie object ready to be loaded, based on the provided
 * title.
 *
 * You must call either `-load` or `-populate:` to populate the object with
 * data.
 *
 * @param title The name of the movie to be looked up.
 * @return An empty movie object ready to be loaded.
 */
- (instancetype)initWithTitle:(NSString *)title;

/**
 * Creates a fetch request for the movie with the provided name, and returns an
 * object representing that movie.
 *
 * You must call either `-load` or `-populate:` to populate the object with
 * data.
 *
 * @param title The name of the movie to be looked up.
 * @param year The year the movie was released. This is only a hint and not a
 * requirement for the returned movie.
 * @return An empty movie object ready to be loaded.
 */
- (instancetype)initWithTitle:(NSString *)title year:(NSUInteger)year;

/** @name Loading Data */

- (void)load:(TMDBMovieFetchOptions)options completion:(TMDBMovieFetchCompletionBlock)completionBlock;

- (void)populate:(NSDictionary *)d;

#pragma mark - Basic Information
/** @name Basic Information */

@property (nonatomic, readonly) TMDBMovieFetchOptions options;

/** The TMDb ID of the movie. */
@property (nonatomic, readonly) NSInteger tmdbID;

/** The title of the movie. */
@property (nonatomic, copy, readonly) NSString *title;

/** The original title of the movie. */
@property (nonatomic, copy, readonly) NSString *originalTitle;

/** A description of the movie. */
@property (nonatomic, copy, readonly) NSString *overview;

/** The tagline of the movie. */
@property (nonatomic, copy, readonly) NSString *tagline;

/** An array of NSStrings representing the categories of the movie. */
@property (nonatomic, strong, readonly) NSArray *categories;

/** An array of NSStrings representing the keywords of the movie. */
@property (nonatomic, strong, readonly) NSArray *keywords;

/** @name Times and Dates */

/** The release date of the movie. */
@property (nonatomic, copy, readonly) NSDate *released;

/**
 * The year in which the movie was released.
 *
 * This is simply a convenience property that uses the `released` date property.
 */
@property (nonatomic, readonly) NSUInteger year;

/** The runtime of the movie in minutes. */
@property (nonatomic, readonly) NSUInteger runtime;

/** @name Other Information */

/** A Boolean value indicating if the movie is an adult movie. */
@property (nonatomic, readonly, getter=isAdult) BOOL adult;

/** The number of votes for this movie from users on the TMDb website. */
@property (nonatomic, readonly) NSInteger votes;

/**
 * The raw contents from the API itself.
 *
 * You can use this property to extract values that iTMDb does not already wrap
 * in the TMDBMovie object.
 */
@property (nonatomic, strong, readonly) id rawResults;

/** @name Imagery */
/**
 * An array of TMDBImage objects that represent the posters used for this
 * movie.
 */
@property (nonatomic, strong, readonly) NSArray *posters;

/**
 * An array of TMDBImage objects that represent the backdrops used on the TMDb
 * website.
 */
@property (nonatomic, strong, readonly) NSArray *backdrops;

/** @name External Resources */
/** The URL of an official website of the movie. */
@property (nonatomic, copy, readonly) NSURL *homepage;

/** The URL of the movie's page on the TMDb website. */
@property (nonatomic, copy, readonly) NSURL *url;

/**
 * The ID of the movie on IMDb.
 *
 * The value of this string includes the `tt` prefix used by IMDb.
 */
@property (nonatomic, copy, readonly) NSString *imdbID;

/** @name Localization */

/**
 * An array of `TMDBLanguage` objects representing the languages spoken in the
 * movie.
 */
@property (nonatomic, strong, readonly) NSArray *languagesSpoken;

/**
 * An array of NSStrings representing the countries that have either co-produced
 * the movie or the countries in which the movie was shot.
 */
@property (nonatomic, strong, readonly) NSArray *countries;

/** @name Getting the Cast and Crew */
/**
 * An array of `TMDBPerson` objects representing the cast and crew of the movie.
 */
@property (nonatomic, strong, readonly) NSArray *cast;

// TODO: Move out of TMDBMovie
+ (NSUInteger)yearFromDate:(NSDate *)date;
+ (NSDate *)dateFromString:(NSString *)dateString;

@end

@class TMDB;

@interface TMDBMovie (UnavailableMethods)

/**
 * Creates a fetch request for the movie with the provided TMDb ID, and returns
 * an object representing that movie.
 *
 * The context gets notified using [TMDB movieDidFinishLoading:] when the movie
 * object has finished loading.
 *
 * @param anID The TMDb ID of the movie to be looked up.
 * @param context The IMDb context from which the lookup should be made.
 * @return An object representing the movie.
 */
+ (instancetype)movieWithID:(NSUInteger)anID options:(TMDBMovieFetchOptions)options context:(TMDB *)context __attribute__((unavailable("Use -initWithID:options: instead.")));

/**
 * Creates a fetch request for the movie with the provided name, and returns an
 * object representing that movie.
 *
 * The context gets notified using [TMDB movieDidFinishLoading:] when the movie
 * object has finished loading.
 *
 * @param aName The name of the movie to be looked up.
 * @param context The IMDb context from which the lookup should be made.
 * @return An object representing the movie.
 */
+ (instancetype)movieWithName:(NSString *)name options:(TMDBMovieFetchOptions)options context:(TMDB *)context __attribute__((unavailable("Use -initWithName:options: instead.")));

/**
 * Creates a fetch request for the movie with the provided name, and returns an
 * object representing that movie.
 *
 * The context gets notified using [TMDB movieDidFinishLoading:] when the movie
 * object has finished loading.
 *
 * @param aName The name of the movie to be looked up.
 * @param aYear The year the movie was released. This is only a hint and not a
 * requirement for the returned movie.
 * @param context The IMDb context from which the lookup should be made.
 * @return An object representing the movie.
 */
+ (instancetype)movieWithName:(NSString *)name year:(NSUInteger)year options:(TMDBMovieFetchOptions)options context:(TMDB *)context __attribute__((unavailable("Use -initWithName:year:options: instead.")));

- (instancetype)initWithID:(NSUInteger)anID options:(TMDBMovieFetchOptions)options context:(TMDB *)context __attribute__((unavailable("Use -initWithID:options: instead.")));

- (instancetype)initWithName:(NSString *)name options:(TMDBMovieFetchOptions)options context:(TMDB *)context __attribute__((unavailable("Use -initWithName:options: instead.")));

- (instancetype)initWithName:(NSString *)name year:(NSUInteger)year options:(TMDBMovieFetchOptions)options context:(TMDB *)context __attribute__((unavailable("Use -initWithName:year:options: instead.")));

/** The original language of the movie. */
@property (nonatomic, copy, readonly) NSString *language UNAVAILABLE_ATTRIBUTE;

/** The censorship certification for this movie. */
@property (nonatomic, copy, readonly) NSString *certification UNAVAILABLE_ATTRIBUTE;

/** A Boolean value indicating if the movie information has been translated. */
@property (nonatomic, readonly, getter=isTranslated) BOOL translated UNAVAILABLE_ATTRIBUTE;

@end
