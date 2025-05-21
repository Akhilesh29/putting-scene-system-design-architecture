# Putting Scene - Block Architecture

## System Overview

```
┌─────────────────────────────────────────────────────────────────────────┐
│                           Client Applications                            │
│  ┌─────────────┐  ┌─────────────┐  ┌─────────────┐  ┌─────────────┐    │
│  │  Web App    │  │ Mobile App  │  │  Admin UI   │  │  API Users  │    │
│  └─────────────┘  └─────────────┘  └─────────────┘  └─────────────┘    │
└───────────────────────────┬─────────────────────────────────────────────┘
                            │
                            ▼
┌─────────────────────────────────────────────────────────────────────────┐
│                           API Gateway Layer                             │
│  ┌─────────────────────────────────────────────────────────────────┐    │
│  │  • Request Routing                                             │    │
│  │  • Rate Limiting                                              │    │
│  │  • Authentication/Authorization                               │    │
│  │  • Request/Response Transformation                            │    │
│  └─────────────────────────────────────────────────────────────────┘    │
└───────────────────────────┬─────────────────────────────────────────────┘
                            │
                            ▼
┌─────────────────────────────────────────────────────────────────────────┐
│                        Core Service Layer                               │
│  ┌─────────────┐  ┌─────────────┐  ┌─────────────┐  ┌─────────────┐    │
│  │ Event       │  │ Venue       │  │ User        │  │ Search      │    │
│  │ Service     │◄─┤ Service     │◄─┤ Service     │◄─┤ Service     │    │
│  └─────┬───────┘  └─────┬───────┘  └─────┬───────┘  └─────┬───────┘    │
└────────┼────────────────┼────────────────┼────────────────┼────────────┘
         │                │                │                │
         ▼                ▼                ▼                ▼
┌─────────────────────────────────────────────────────────────────────────┐
│                        Data Access Layer                                │
│  ┌─────────────┐  ┌─────────────┐  ┌─────────────┐  ┌─────────────┐    │
│  │ PostgreSQL  │  │ Redis Cache │  │ Elastic     │  │ File        │    │
│  │ Database    │  │ Layer       │  │ Search      │  │ Storage     │    │
│  └─────────────┘  └─────────────┘  └─────────────┘  └─────────────┘    │
└─────────────────────────────────────────────────────────────────────────┘
```

## Component Details

### 1. Client Applications
- **Web Application**: React-based SPA for end users
- **Mobile Application**: Native iOS/Android apps
- **Admin UI**: Management interface for event organizers
- **API Users**: Third-party integrations

### 2. API Gateway Layer
- **Request Routing**: Routes requests to appropriate microservices
- **Rate Limiting**: Prevents abuse and ensures fair usage
- **Authentication**: JWT-based authentication
- **Authorization**: Role-based access control
- **Request/Response Transformation**: API versioning and format conversion

### 3. Core Service Layer

#### Event Service
```
┌─────────────────────────────────────────────────────────┐
│                     Event Service                        │
├─────────────────────────────────────────────────────────┤
│  • Event CRUD Operations                                │
│  • Ticket Management                                    │
│  • Event Scheduling                                     │
│  • Event Analytics                                      │
└─────────────────────────────────────────────────────────┘
```

#### Venue Service
```
┌─────────────────────────────────────────────────────────┐
│                     Venue Service                        │
├─────────────────────────────────────────────────────────┤
│  • Venue Management                                     │
│  • Location Services                                     │
│  • Capacity Management                                   │
│  • Amenity Tracking                                      │
└─────────────────────────────────────────────────────────┘
```

#### User Service
```
┌─────────────────────────────────────────────────────────┐
│                     User Service                         │
├─────────────────────────────────────────────────────────┤
│  • User Management                                      │
│  • Authentication                                       │
│  • Preferences                                          │
│  • Notifications                                        │
└─────────────────────────────────────────────────────────┘
```

#### Search Service
```
┌─────────────────────────────────────────────────────────┐
│                     Search Service                       │
├─────────────────────────────────────────────────────────┤
│  • Full-text Search                                     │
│  • Geospatial Search                                    │
│  • Filtering                                            │
│  • Sorting                                              │
└─────────────────────────────────────────────────────────┘
```

### 4. Data Access Layer

#### PostgreSQL Database Schema
```
┌─────────────┐    ┌─────────────┐    ┌─────────────┐
│   Events    │    │   Venues    │    │   Users     │
├─────────────┤    ├─────────────┤    ├─────────────┤
│ id          │    │ id          │    │ id          │
│ title       │    │ name        │    │ email       │
│ description │    │ location    │    │ password    │
│ start_time  │    │ capacity    │    │ role        │
│ end_time    │    │ amenities   │    │ created_at  │
│ venue_id    │    │ created_at  │    │ updated_at  │
│ price       │    │ updated_at  │    └─────────────┘
│ tickets     │    └─────────────┘
└─────────────┘
```

#### Redis Cache Structure
```
┌─────────────────────────────────────────────────────────┐
│                     Redis Cache                          │
├─────────────────────────────────────────────────────────┤
│  • Event Cache: event:{id}                              │
│  • Venue Cache: venue:{id}                              │
│  • User Session: session:{token}                        │
│  • Rate Limiting: rate:{ip}                             │
└─────────────────────────────────────────────────────────┘
```

## Data Flow

1. **Event Creation Flow**:
```
Client → API Gateway → Event Service → PostgreSQL
                              ↓
                        Redis Cache
```

2. **Search Flow**:
```
Client → API Gateway → Search Service → Elasticsearch
                              ↓
                        Redis Cache
```

3. **User Authentication Flow**:
```
Client → API Gateway → User Service → PostgreSQL
                              ↓
                        Redis Cache
```

## Performance Optimizations

1. **Caching Strategy**:
   - L1 Cache: In-memory cache for frequently accessed data
   - L2 Cache: Redis for distributed caching
   - Cache invalidation based on event updates

2. **Database Optimization**:
   - Indexed fields for common queries
   - Partitioned tables for large datasets
   - Connection pooling

3. **Search Optimization**:
   - Elasticsearch for full-text search
   - Geospatial indexing for location-based queries
   - Result caching

4. **API Optimization**:
   - Response compression
   - Pagination
   - Field filtering 