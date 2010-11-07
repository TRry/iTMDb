//
//  TMDBMovie.h
//  iTMDb
//
//  Created by Christian Rasmussen on 04/11/10.
//  Copyright 2010 Apoltix. All rights reserved.
//

#import <Cocoa/Cocoa.h>

@class TMDB;

#import "TMDBRequest.h"
#import "TMDBRequestDelegate.h"

@interface TMDBMovie : NSObject <TMDBRequestDelegate> {
	TMDB *_context;
	TMDBRequest *_request;

	NSInteger _id;
	NSArray *_rawResults;
	NSString *_title;
	NSDate *_released;
	NSString *_overview;
	NSUInteger _runtime;
	NSString *_tagline;
	NSURL *_homepage;
	NSString *_imdbID;
}

@property (nonatomic, retain, readonly) TMDB *context;

@property (nonatomic, retain, readonly) NSArray *rawResults;
@property (nonatomic, assign, readonly) NSInteger id;
@property (nonatomic, retain, readonly) NSString *title;
@property (nonatomic, retain, readonly) NSDate *released;
@property (nonatomic, retain, readonly) NSString *overview;
@property (nonatomic, assign, readonly) NSUInteger runtime;
@property (nonatomic, retain, readonly) NSString *tagline;
@property (nonatomic, retain, readonly) NSURL *homepage;
@property (nonatomic, retain, readonly) NSString *imdbID;

+ (TMDBMovie *)movieWithID:(NSInteger)anID context:(TMDB *)context;

- (id)initWithID:(NSInteger)anID context:(TMDB *)context;

@end