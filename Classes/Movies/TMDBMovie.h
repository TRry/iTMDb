//
//  TMDBMovie.h
//  iTMDb
//
//  Created by Christian Rasmussen on 04/11/10.
//  Copyright 2010 Apoltix. All rights reserved.
//

#import <Cocoa/Cocoa.h>

@class TMDB;

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

/** @name Creating an Instance */

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
+ (instancetype)movieWithID:(NSUInteger)anID options:(TMDBMovieFetchOptions)options context:(TMDB *)context;

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
+ (instancetype)movieWithName:(NSString *)aName options:(TMDBMovieFetchOptions)options context:(TMDB *)context;

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
+ (instancetype)movieWithName:(NSString *)aName year:(NSUInteger)aYear options:(TMDBMovieFetchOptions)options context:(TMDB *)context;

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
- (instancetype)initWithID:(NSUInteger)anID options:(TMDBMovieFetchOptions)options context:(TMDB *)context;

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
- (instancetype)initWithName:(NSString *)aName options:(TMDBMovieFetchOptions)options context:(TMDB *)context;

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
- (instancetype)initWithName:(NSString *)aName year:(NSUInteger)aYear options:(TMDBMovieFetchOptions)options context:(TMDB *)context;

/** @name Basic Information */

/** The `TMDB` context that created the instance. */
@property (nonatomic, strong, readonly) TMDB *context;

@property (nonatomic, readonly) TMDBMovieFetchOptions options;

/** The TMDb ID of the movie. */
@property (nonatomic, readonly) NSInteger id;

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

/** The censorship certification for this movie. */
@property (nonatomic, copy, readonly) NSString *certification;

@property (nonatomic, strong, readonly) NSDictionary *userData;

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
 * The value of this string includes the "<code>tt</code>" prefix used by IMDb.
 */
@property (nonatomic, copy, readonly) NSString *imdbID;

/** @name Metadata */

/** A Boolean value indicating if the movie information has been translated. */
@property (nonatomic, readonly, getter=isTranslated) BOOL translated;

/** @name Localization */

/** The original language of the movie. */
@property (nonatomic, copy, readonly) NSString *language;

/**
 * An array of NSStrings representing the languages spoken in the movie.
 *
 * The values of this array can represent either the languages spoken in the
 * original language track, or the different language tracks available for the
 * movie. Either is not specified.
 */
@property (nonatomic, strong, readonly) NSArray *languagesSpoken;

/**
 * An array of NSStrings representing the countries that have either co-produced
 * the movie or the countries in which the movie was shot. */
@property (nonatomic, strong, readonly) NSArray *countries;

/** @name Getting the Cast and Crew */
/**
 * An array of `TMDBPerson` objects representing the cast and crew of the movie.
 */
@property (nonatomic, strong, readonly) NSArray *cast;

@end