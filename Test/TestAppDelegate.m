//
//  TestAppDelegate.m
//  iTMDb
//
//  Created by Christian Rasmussen on 04/11/10.
//  Copyright 2010 Apoltix. All rights reserved.
//

#import "TestAppDelegate.h"

@implementation TestAppDelegate

@synthesize window;

- (void)awakeFromNib
{
	tmdb = nil;

	[allDataTextView setFont:[NSFont fontWithName:@"Lucida Console" size:11.0]];
}

#pragma mark -
- (IBAction)go:(id)sender
{
	if (!([[apiKey stringValue] length] > 0 && [movieID integerValue] > 0))
	{
		NSAlert *alert = [NSAlert alertWithMessageText:@"Missing either API key or movie ID"
										 defaultButton:@"OK"
									   alternateButton:nil
										   otherButton:nil
							 informativeTextWithFormat:@"Please enter both API key and movie ID.\n\n"
													   @"You can obtain an API key from themoviedb.org."];
		[alert beginSheetModalForWindow:window modalDelegate:nil didEndSelector:nil contextInfo:nil];

		return;
	}

	[throbber startAnimation:self];
	[goButton setEnabled:NO];
	[viewAllDataButton setEnabled:NO];

	tmdb = [[TMDB alloc] initWithAPIKey:[apiKey stringValue] delegate:self];

	[tmdb movieWithID:[movieID integerValue]];
}

- (IBAction)viewAllData:(id)sender
{
	if (!allData)
		return;

	[allDataTextView setString:[allData description]];

	[allDataWindow makeKeyAndOrderFront:self];
}

#pragma mark -
#pragma mark TMDBDelegate

- (void)tmdb:(TMDB *)context didFinishLoadingMovie:(TMDBMovie *)movie
{
	printf("%s\n", [[movie description] UTF8String]);

	[movieTitle setStringValue:movie.title];
	[movieOverview setString:movie.overview];
	[movieRuntime setStringValue:[NSString stringWithFormat:@"%lu", movie.runtime]];

	NSDateFormatter *releaseDateFormatter = [[NSDateFormatter alloc] init];
	[releaseDateFormatter setDateFormat:@"dd-MM-yyyy"];
	[movieReleaseDate setStringValue:[releaseDateFormatter stringFromDate:movie.released]];

	NSUInteger posterSizeCount = 0;
	for (TMDBImage *poster in movie.posters)
		posterSizeCount += [poster sizeCount];
	[moviePostersCount setStringValue:[NSString stringWithFormat:@"%lu (%lu sizes total)", [movie.posters count], posterSizeCount]];
	NSUInteger backdropSizeCount = 0;
	for (TMDBImage *backdrop in movie.backdrops)
		backdropSizeCount += [backdrop sizeCount];
	[movieBackdropsCount setStringValue:[NSString stringWithFormat:@"%lu (%lu sizes total)", [movie.backdrops count], backdropSizeCount]];

	allData = [[NSArray alloc] initWithArray:movie.rawResults copyItems:YES];

	[context release];
	//[movie release];

	[throbber stopAnimation:self];
	[goButton setEnabled:YES];

	[viewAllDataButton setEnabled:YES];
}
		
- (void)tmdb:(TMDB *)context didFailLoadingMovie:(TMDBMovie *)movie error:(NSError *)error
{
	[context release];
	//[movie release];

	NSAlert *alert = [NSAlert alertWithError:error];
	[alert beginSheetModalForWindow:window modalDelegate:nil didEndSelector:nil contextInfo:nil];

	[movieTitle setStringValue:@""];
	[movieOverview setString:@""];
	[movieRuntime setStringValue:@"0"];
	[movieReleaseDate setStringValue:@"00-00-0000"];
	[moviePostersCount setStringValue:@"0 (0 sizes total)"];
	[movieBackdropsCount setStringValue:@"0 (0 sizes total)"];

	[throbber stopAnimation:self];
	[goButton setEnabled:YES];

	[viewAllDataButton setEnabled:NO];

}

@end