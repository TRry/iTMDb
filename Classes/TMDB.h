//
//  TMDB.h
//  iTMDb
//
//  Created by Christian Rasmussen on 04/11/10.
//  Copyright 2010 Apoltix. All rights reserved.
//

#import <Cocoa/Cocoa.h>

#import "TMDBDelegate.h"
#import "TMDBToken.h"
#import "TMDBMovie.h"

@interface TMDB : NSObject {
	id <TMDBDelegate> _delegate;
	NSString *_apiKey;
	NSString *_language;

	TMDBToken *token;
}

@property (nonatomic, retain) id <TMDBDelegate> delegate;
@property (nonatomic, retain) NSString *apiKey;
@property (nonatomic, retain) NSString *language;

@property (nonatomic, retain, readonly) TMDBToken *token;

- (id)initWithAPIKey:(NSString *)anApiKey delegate:(id <TMDBDelegate>)aDelegate;
- (id)initWithAPIKey:(NSString *)anApiKey delegate:(id <TMDBDelegate>)aDelegate language:(NSString *)aLanguage;

#pragma mark -
#pragma mark Notifications
- (void)movieDidFinishLoading:(TMDBMovie *)aMovie;
- (void)movieDidFailLoading:(TMDBMovie *)aMovie error:(NSError *)error;

#pragma mark -
#pragma mark Shortcuts
- (TMDBMovie *)movieWithID:(NSInteger)anID;
- (TMDBMovie *)movieWithName:(NSString *)aName;

@end