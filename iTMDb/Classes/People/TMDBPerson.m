//
//  TMDBPerson.m
//  iTMDb
//
//  Created by Christian Rasmussen on 29/12/10.
//  Copyright 2010 Apoltix. All rights reserved.
//

#import "TMDBPerson.h"
#import "TMDBMovie.h"
#import "TMDB.h"
#import "TMDBRequest.h"

@implementation TMDBPerson

+ (NSArray *)personsWithMovie:(TMDBMovie *)movie personsInfo:(NSArray *)d
{
	NSMutableArray *persons = [NSMutableArray arrayWithCapacity:[d count]];

	for (NSDictionary *rawPerson in d) {
		TMDBPerson *person = [[TMDBPerson alloc] initWithMovie:movie personInfo:rawPerson];
		[persons addObject:person];
	}

	return [NSArray arrayWithArray:persons];
}

- (instancetype)initWithID:(NSUInteger)personID
{
	if (!(self = [super init]))
		return nil;

	_id = personID;

	return self;
}

- (instancetype)initWithMovie:(TMDBMovie *)movie personInfo:(NSDictionary *)d
{
	if (!(self = [self initWithID:0]))
		return nil;

	_movie = movie;
	_context = movie.context;

	if (d != nil)
		[self populate:d];

	return self;
}

#pragma mark -

- (NSString *)description
{
	if (_movie != nil && [_character length] > 0 && [_name length] > 0) {
		return [NSString stringWithFormat:@"<%@ %p: %@ as \"%@\" in \"%@\"%@>", [self class], self, _name, _character, _movie.title, _movie.year > 0 ? [NSString stringWithFormat:@" (%zd)", _movie.year] : @"", nil];
	}
	else if (_movie != nil && [_name length] > 0 && [_job length] > 0) {
		return [NSString stringWithFormat:@"<%@ %p: %@ as %@ of \"%@\"%@>", [self class], self, _name, _job, _movie.title, _movie.year > 0 ? [NSString stringWithFormat:@" (%zd)", _movie.year] : @"", nil];
	}
	else if (_movie != nil && [_name length] > 0) {
		return [NSString stringWithFormat:@"<%@ %p: %@ in \"%@\"%@>", [self class], self, _name, _movie.title, _movie.year > 0 ? [NSString stringWithFormat:@" (%zd)", _movie.year] : @"", nil];
	}
	else if ([_name length] > 0) {
		return [NSString stringWithFormat:@"<%@ %p: %@>", [self class], self, _name, nil];
	}

	return [NSString stringWithFormat:@"<%@ %p>", [self class], self];
}

#pragma mark -

- (void)populate:(NSDictionary *)d
{
	_id = [TMDB_NSNumberOrNil(d[@"id"]) unsignedIntegerValue];
	_name = [TMDB_NSStringOrNil(d[@"name"]) copy];
	_character = [TMDB_NSStringOrNil(d[@"character"]) copy];
	_job = [TMDB_NSStringOrNil(d[@"job"]) copy];
	if (_job == nil)
		_job = @"Actor"; // TODO: Use different/more permanent identifier
	_url = TMDB_NSURLOrNilFromStringOrNil(d[@"url"]);
	_order = [TMDB_NSNumberOrNil(d[@"order"]) unsignedIntegerValue];
	_castID = [TMDB_NSNumberOrNil(d[@"cast_id"]) integerValue];
	_imageURL = TMDB_NSURLOrNilFromStringOrNil(d[@"profile_path"]); // TODO: Validate URL fragment
}

#pragma mark - Updating

- (void)update:(TMDBPersonUpdateCompletionBlock)completionBlock
{
	[self update:TMDBPersonUpdateOptionBasic completion:completionBlock];
}

- (void)update:(TMDBPersonUpdateOptions)options completion:(TMDBPersonUpdateCompletionBlock)completionBlock
{
	NSURL *url = [NSURL URLWithString:[TMDBAPIURLBase stringByAppendingFormat:@"%@/person/%zd?api_key=%@&language=%@",
									   TMDBAPIVersion, _id, _context.apiKey, _context.language]];

	[TMDBRequest requestWithURL:url completionBlock:^(id parsedData) {
		NSLog(@"%@", parsedData);
	}];
}

@end